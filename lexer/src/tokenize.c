/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 11:10:43 by yboumlak          #+#    #+#             */
/*   Updated: 2024/07/16 20:26:04 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lexer.h"

t_tree_node	*parse(t_token **tokens);

t_token	*create_token(t_token_type type, char *value, t_quote state)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->type = type;
	token->value = value;
	token->state = state;
	token->subtokens = NULL;
	token->next = NULL;
	return (token);
}

t_token	*get_next_token(char **input)
{
	char	*start;
	char	*value;
	int		open_parentheses;
	int		nesting_level;
	char	*subshell_input;
	t_token	*subshell_token;
	t_token	*last_token;
	t_token	*token;
	t_quote	state;
	char	quote_type;
	int		quote_count;
	t_quote	quote_state;
	int		unattached_quote;

	state = NORMAL;
	if (**input == '\0')
		return (create_token(TOKEN_EOF, "", state));
	if (isspace(**input))
	{
		start = *input;
		while (isspace(**input))
			(*input)++;
		value = strndup(start, *input - start);
		return (create_token(TOKEN_WHITESPACE, value, state));
	}
	else if (**input == '|')
	{
		if (*(*input + 1) == '|')
		{
			(*input) += 2;
			return (create_token(TOKEN_OR, "||", state));
		}
		(*input)++;
		return (create_token(TOKEN_PIPE, "|", state));
	}
	else if (**input == '<')
	{
		if (*(*input + 1) == '<')
		{
			(*input) += 2;
			return (create_token(TOKEN_HEREDOC, "<<", state));
		}
		(*input)++;
		return (create_token(TOKEN_REDIR_IN, "<", state));
	}
	else if (**input == '>')
	{
		if (*(*input + 1) == '>')
		{
			(*input) += 2;
			return (create_token(TOKEN_REDIR_APPEND, ">>", state));
		}
		(*input)++;
		return (create_token(TOKEN_REDIR_OUT, ">", state));
	}
	else if (**input == '&')
	{
		if (*(*input + 1) == '&')
		{
			(*input) += 2;
			return (create_token(TOKEN_AND, "&&", state));
		}
	}
	else if (**input == '(')
	{
		(*input)++;
		start = *input;
		nesting_level = 1;
		while (nesting_level > 0 && **input != '\0')
		{
			if (**input == '(')
				nesting_level++;
			else if (**input == ')')
				nesting_level--;
			(*input)++;
		}
		if (nesting_level == 0)
		{
			value = strndup(start, *input - start - 1);
			subshell_input = value;
			subshell_token = create_token(TOKEN_SUBSHELL, value, state);
			last_token = NULL;
			while ((token = get_next_token(&subshell_input))->type != TOKEN_EOF)
			{
				if (last_token == NULL)
					subshell_token->subtokens = token;
				else
					last_token->next = token;
				last_token = token;
			}
			return (subshell_token);
		}
		else
		{
			fprintf(stderr, "Syntax error: missing closing parenthesis\n");
			return (create_token(TOKEN_UNKNOWN, "", state));
		}
	}
	else if (**input == '\'' || **input == '"')
	{
		quote_type = **input;
		if (**input == '\"')
			state = IN_DQUOTES;
		else
			state = IN_QUOTES;
		(*input)++;
		start = *input;
		while (**input != '\0')
		{
			if (**input == quote_type)
			{
				value = strndup(start, *input - start);
				(*input)++;
				return (create_token(TOKEN_WORD, value, state));
			}
			(*input)++;
		}
		fprintf(stderr, "Syntax error: unmatched quote\n");
		return (create_token(TOKEN_UNKNOWN, "", state));
	}
	else
	{
		start = *input;
		while (!isspace(**input) && !strchr("<>|&\"\'", **input))
			(*input)++;
		value = strndup(start, *input - start);
		return (create_token(TOKEN_WORD, value, state));
	}
	return (create_token(TOKEN_UNKNOWN, "", state));
}

t_token	*tokenize(char *input)
{
	t_token	*head;
	t_token	*tail;
	t_token	*token;

	head = NULL;
	tail = NULL;
	while ((token = get_next_token(&input))->type != TOKEN_EOF)
	{
		if (head == NULL)
			head = token;
		else
			tail->next = token;
		tail = token;
	}
	if (tail != NULL)
		tail->next = token;
	return (head);
}

t_tree_node	*create_tree_node(t_token *token)
{
	t_tree_node	*node;

	node = malloc(sizeof(t_tree_node));
	node->token = token;
	node->left = NULL;
	node->right = NULL;
	node->redirections = NULL;
	return (node);
}

void	add_redirection(t_tree_node *node, t_token *token)
{
	t_redirection	*redir;
	t_redirection	*current;
	t_token			*file_token;

	redir = malloc(sizeof(t_redirection));
	redir->type = token->type;
	file_token = token->next;
	while (file_token && file_token->type == TOKEN_WHITESPACE)
		file_token = file_token->next;
	if (file_token)
		redir->file = strdup(file_token->value);
	else
		redir->file = NULL;
	redir->fd = -1;
	if (token->type == TOKEN_HEREDOC)
		redir->delimiter = strdup(file_token->value);
	else
		redir->delimiter = NULL;
	redir->next = NULL;
	if (!node->redirections)
		node->redirections = redir;
	else
	{
		current = node->redirections;
		while (current->next)
			current = current->next;
		current->next = redir;
	}
}

void	parse_redirections(t_tree_node *node, t_token **tokens)
{
	while (*tokens && ((*tokens)->type == TOKEN_REDIR_IN
			|| (*tokens)->type == TOKEN_REDIR_OUT
			|| (*tokens)->type == TOKEN_REDIR_APPEND
			|| (*tokens)->type == TOKEN_HEREDOC))
	{
		add_redirection(node, *tokens);
		*tokens = (*tokens)->next;
		while (*tokens && (*tokens)->type == TOKEN_WHITESPACE)
			*tokens = (*tokens)->next;
		if (*tokens)
			*tokens = (*tokens)->next;
	}
}

t_tree_node	*parse_subshell(t_token **tokens);

t_tree_node	*parse_command(t_token **tokens)
{
	t_tree_node	*node;
	t_tree_node	*current;
	char		*value;
	t_token		*next;
	t_tree_node	*subshell_node;

	node = NULL;
	current = NULL;
	while (*tokens && ((*tokens)->type == TOKEN_WORD
			|| (*tokens)->type == TOKEN_WHITESPACE
			|| (*tokens)->type == TOKEN_SUBSHELL))
	{
		if ((*tokens)->type == TOKEN_WHITESPACE)
		{
			*tokens = (*tokens)->next;
			continue ;
		}
		if ((*tokens)->type == TOKEN_SUBSHELL)
		{
			subshell_node = parse_subshell(tokens);
			if (node == NULL)
			{
				node = subshell_node;
				current = node;
			}
			else
			{
				current->right = subshell_node;
				current = current->right;
			}
			continue ;
		}
		while ((*tokens)->type == TOKEN_WORD && (*tokens)->next
			&& (*tokens)->next->type == TOKEN_WORD)
		{
			value = ft_strjoin((*tokens)->value, (*tokens)->next->value);
			free((*tokens)->value);
			(*tokens)->value = value;
			next = (*tokens)->next;
			(*tokens)->next = next->next;
			free(next);
		}
		if (node == NULL)
		{
			node = create_tree_node(*tokens);
			current = node;
		}
		else
		{
			current->right = create_tree_node(*tokens);
			current = current->right;
		}
		*tokens = (*tokens)->next;
	}
	if (node)
		parse_redirections(node, tokens);
	return (node);
}

t_tree_node	*parse_pipe(t_token **tokens)
{
	t_tree_node	*left;
	t_tree_node	*node;

	left = parse_command(tokens);
	while (*tokens != NULL && (*tokens)->type == TOKEN_PIPE)
	{
		node = create_tree_node(*tokens);
		*tokens = (*tokens)->next;
		node->left = left;
		node->right = parse_command(tokens);
		left = node;
	}
	return (left);
}

t_tree_node	*parse_and_or(t_token **tokens)
{
	t_tree_node	*left;
	t_tree_node	*node;

	left = parse_pipe(tokens);
	while (*tokens != NULL && ((*tokens)->type == TOKEN_AND
			|| (*tokens)->type == TOKEN_OR))
	{
		node = create_tree_node(*tokens);
		*tokens = (*tokens)->next;
		node->left = left;
		node->right = parse_pipe(tokens);
		left = node;
	}
	return (left);
}

t_tree_node	*parse_subshell(t_token **tokens)
{
	t_tree_node	*node;
	t_token		*subshell_tokens;
	t_token		*token;

	if (*tokens == NULL || (*tokens)->type != TOKEN_SUBSHELL)
		return (NULL);
	token = *tokens;
	subshell_tokens = token->subtokens;
	node = create_tree_node(token);
	*tokens = (*tokens)->next;
	node->left = parse(&subshell_tokens);
	return (node);
}

t_tree_node	*parse(t_token **tokens)
{
	return (parse_and_or(tokens));
}

void	print_token(t_token *token)
{
	if (token == NULL)
		return ;
	printf("Token type: %d, value: %s, state: %d\n", token->type, token->value,
		token->state);
	if (token->subtokens != NULL)
	{
		printf("Subtokens:\n");
		print_token(token->subtokens);
	}
	if (token->next != NULL)
	{
		printf("Next token:\n");
		print_token(token->next);
	}
}

void	print_redirections(t_redirection *redirection, char *indent)
{
	while (redirection != NULL)
	{
		printf("%sRedirection type: %d, file: %s, delimiter: %s\n", indent,
			redirection->type, redirection->file,
			redirection->delimiter ? redirection->delimiter : "NULL");
		redirection = redirection->next;
	}
}

void	print_tree(t_tree_node *node, char *indent, bool is_last)
{
	char	new_indent[100];

	if (node == NULL)
		return ;
	printf("%s", indent);
	strcpy(new_indent, indent);
	if (is_last)
	{
		printf("└──");
		strcat(new_indent, "    ");
	}
	else
	{
		printf("├──");
		strcat(new_indent, "│   ");
	}
	if (node->token)
		printf("%s\n", node->token->value);
	else
		printf("NULL\n");
	print_redirections(node->redirections, new_indent);
	if (node->left || node->right)
	{
		if (node->left)
			print_tree(node->left, new_indent, node->right == NULL);
		if (node->right)
			print_tree(node->right, new_indent, true);
	}
}

int	main(void)
{
	char		*input;
	t_token		*tokens;
	t_tree_node	*tree;

	input = "(cat file.txt | wc -l > count.txt) && echo 'true'";
	tokens = tokenize(input);
	// print_token(tokens);
	tree = parse(&tokens);
	print_tree(tree, "", true);
	return (0);
}
