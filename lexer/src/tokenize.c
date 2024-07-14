/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 11:10:43 by yboumlak          #+#    #+#             */
/*   Updated: 2024/07/14 19:58:13 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lexer.h"

t_tree_node	*parse(t_token **tokens);

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
			if (start != *input)
			{
				value = strndup(start, *input - start);
				(*input)++;
				return (create_token(TOKEN_WORD, value));
			}
			(*input)++;
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
			(*input)++;
		if (**input == '\'')
		{
			if (start != *input)
			{
				value = strndup(start, *input - start);
				(*input)++;
				return (create_token(TOKEN_WORD, value));
			}
			(*input)++;
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
		while (**input && !strchr("|&()<>\"\'", **input))
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
	node->redirections = NULL;
	return (node);
}

void	add_redirection(t_tree_node *node, t_token *token)
{
	t_redirection	*redir;
	t_redirection	*current;

	redir = malloc(sizeof(t_redirection));
	redir->type = token->type;
	redir->file = strdup(token->next->value);
	if (token->type == TOKEN_HEREDOC)
		redir->delimiter = strdup(token->next->value);
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
		*tokens = (*tokens)->next->next;
	}
}

t_tree_node	*parse_subshell(t_token **tokens);

t_tree_node	*parse_command(t_token **tokens)
{
	t_tree_node	*node;
	t_tree_node	*current;

	if (*tokens != NULL && (*tokens)->type == TOKEN_SUBSHELL)
	{
		return (parse_subshell(tokens));
	}
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

void	print_redirections(t_redirection *redirections, int depth)
{
	t_redirection	*current;

	current = redirections;
	while (current)
	{
		for (int i = 0; i < depth; i++)
		{
			printf("    ");
		}
		switch (current->type)
		{
		case TOKEN_REDIR_IN:
			printf("REDIRECT_IN(%s)\n", current->file);
			break ;
		case TOKEN_REDIR_OUT:
			printf("REDIRECT_OUT(%s)\n", current->file);
			break ;
		case TOKEN_REDIR_APPEND:
			printf("APPEND(%s)\n", current->file);
			break ;
		case TOKEN_HEREDOC:
			printf("HEREDOC_DILIM(%s)\n", current->delimiter);
			break ;
		default:
			printf("UNKNOWN_REDIRECT\n");
			break ;
		}
		current = current->next;
	}
}

void	print_tree(t_tree_node *node, int depth)
{
	if (node == NULL)
	{
		return ;
	}
	// Print right subtree
	print_tree(node->right, depth + 1);
	// Print current node with indentation
	for (int i = 0; i < depth; i++)
	{
		printf("    ");
	}
	if (node->token != NULL)
	{
		switch (node->token->type)
		{
		case TOKEN_WORD:
			printf("WORD(%s)\n", node->token->value);
			break ;
		case TOKEN_PIPE:
			printf("PIPE(%s)\n", node->token->value);
			break ;
		case TOKEN_AND:
			printf("AND(%s)\n", node->token->value);
			break ;
		case TOKEN_OR:
			printf("OR(%s)\n", node->token->value);
			break ;
		case TOKEN_SUBSHELL:
			printf("SUBSHELL(%s)\n", node->token->value);
			break ;
		default:
			printf("UNKNOWN\n");
			break ;
		}
	}
	// Print redirections
	print_redirections(node->redirections, depth + 1);
	// Print left subtree
	print_tree(node->left, depth + 1);
}

int	main(void)
{
	char		*input;
	t_token		*tokens;
	t_tree_node	*tree;

	input = "ca't' << idk | (''''test'''' -l && ps -e -kfj < fild.txt >> file.txt && (echo test || (wc -l | echo 'yes')))";
	tokens = tokenize(input);
	tree = parse(&tokens);
	print_tree(tree, 0);
	return (0);
}
