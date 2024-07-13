/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 11:10:43 by yboumlak          #+#    #+#             */
/*   Updated: 2024/07/13 19:57:23 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lexer.h"

t_token	*create_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->type = type;
	token->value = strdup(value);
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

	while (isspace(**input))
		(*input)++;
	if (**input == '\0')
		return (create_token(TOKEN_EOF, ""));
	if (**input == '|')
	{
		if (*(*input + 1) == '|')
		{
			(*input) += 2;
			return (create_token(TOKEN_OR, "||"));
		}
		(*input)++;
		return (create_token(TOKEN_PIPE, "|"));
	}
	else if (**input == '<')
	{
		if (*(*input + 1) == '<')
		{
			(*input) += 2;
			return (create_token(TOKEN_HEREDOC, "<<"));
		}
		(*input)++;
		return (create_token(TOKEN_REDIR_IN, "<"));
	}
	else if (**input == '>')
	{
		if (*(*input + 1) == '>')
		{
			(*input) += 2;
			return (create_token(TOKEN_REDIR_APPEND, ">>"));
		}
		(*input)++;
		return (create_token(TOKEN_REDIR_OUT, ">"));
	}
	else if (**input == '&')
	{
		if (*(*input + 1) == '&')
		{
			(*input) += 2;
			return (create_token(TOKEN_AND, "&&"));
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
			subshell_token = create_token(TOKEN_SUBSHELL, value);
			last_token = NULL;
			while ((token = get_next_token(&subshell_input))->type != TOKEN_EOF)
			{
				if (last_token == NULL)
				{
					subshell_token->subtokens = token;
				}
				else
				{
					last_token->next = token;
				}
				last_token = token;
			}
			return (subshell_token);
		}
		else
		{
			fprintf(stderr, "Syntax error: missing closing parenthesis\n");
			return (create_token(TOKEN_UNKNOWN, ""));
		}
	}
	else if (**input == '"')
	{
		(*input)++;
		start = *input;
		while (**input != '"' && **input != '\0')
			(*input)++;
		if (**input == '"')
		{
			value = strndup(start, *input - start);
			(*input)++;
			return (create_token(TOKEN_WORD, value));
		}
		else
		{
			fprintf(stderr, "Syntax error: missing closing double quote\n");
			return (create_token(TOKEN_UNKNOWN, ""));
		}
	}
	else if (**input == '\'')
	{
		(*input)++;
		start = *input;
		while (**input != '\'' && **input != '\0')
		{
			(*input)++;
		}
		if (**input == '\'')
		{
			value = strndup(start, *input - start);
			(*input)++;
			return (create_token(TOKEN_WORD, value));
		}
		else
		{
			fprintf(stderr, "Syntax error: missing closing single quote\n");
			return (create_token(TOKEN_UNKNOWN, ""));
		}
	}
	else
	{
		start = *input;
		while (!isspace(**input) && **input != '\0' && strchr("|<>&();\"",
				**input) == NULL)
		{
			(*input)++;
		}
		if (start != *input)
		{
			value = strndup(start, *input - start);
			return (create_token(TOKEN_WORD, value));
		}
	}
	return (create_token(TOKEN_UNKNOWN, ""));
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
	return (node);
}

void	add_redirection(t_tree_node *node, t_token *token)
{
	t_redirection	*redir;
	t_redirection	*current;

	redir = malloc(sizeof(t_redirection));
	redir->type = token->type;
	redir->file = strdup(token->next->value);
	redir->next = NULL;
	if (token->type == TOKEN_REDIR_IN || token->type == TOKEN_HEREDOC)
	{
		if (!node->input_redirections)
		{
			node->input_redirections = redir;
		}
		else
		{
			current = node->input_redirections;
			while (current->next)
				current = current->next;
			current->next = redir;
		}
	}
	else
	{
		if (!node->output_redirections)
		{
			node->output_redirections = redir;
		}
		else
		{
			current = node->output_redirections;
			while (current->next)
				current = current->next;
			current->next = redir;
		}
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
		*tokens = (*tokens)->next->next;
	}
}

t_tree_node	*parse_command(t_token **tokens)
{
	t_tree_node	*node;
	t_tree_node	*current;

	node = create_tree_node(*tokens);
	current = node;
	*tokens = (*tokens)->next;
	while (*tokens != NULL && (*tokens)->type == TOKEN_WORD)
	{
		current->right = create_tree_node(*tokens);
		current = current->right;
		*tokens = (*tokens)->next;
	}
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

t_tree_node	*parse(t_token **tokens)
{
	return (parse_and_or(tokens));
}

void	print_redirections(t_redirection *redir)
{
	while (redir)
	{
		printf("    Redirection: type = %d, file = %s\n", redir->type,
			redir->file);
		redir = redir->next;
	}
}

void	print_tree(t_tree_node *node, int level)
{
	if (node == NULL)
		return ;
	for (int i = 0; i < level; i++)
		printf("  ");
	printf("%s\n", node->token->value);
	if (node->input_redirections)
	{
		for (int i = 0; i < level; i++)
			printf("  ");
		printf("Input redirections:\n");
		print_redirections(node->input_redirections);
	}
	if (node->output_redirections)
	{
		for (int i = 0; i < level; i++)
			printf("  ");
		printf("Output redirections:\n");
		print_redirections(node->output_redirections);
	}
	print_tree(node->left, level + 1);
	print_tree(node->right, level + 1);
}
int	main(void)
{
	char		*input;
	t_token		*tokens;
	t_tree_node	*tree;

	input = "ls -la | grep < .txt || cat file.l >> file.txt | cat && ls";
	tokens = tokenize(input);
	tree = parse(&tokens);
	print_tree(tree, 0);
	return (0);
}
