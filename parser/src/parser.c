/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:27:02 by yboumlak          #+#    #+#             */
/*   Updated: 2024/07/23 14:44:29 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

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

t_redirection	*parse_redirection(t_token **tokens)
{
	t_redirection	*redir;
	t_token			*file_token;

	redir = malloc(sizeof(t_redirection));
	if (!redir)
		return (NULL);
	redir->type = (*tokens)->type;
	redir->next = NULL;
	file_token = (*tokens)->next;
	while (file_token && file_token->type == TOKEN_WHITESPACE)
		file_token = file_token->next;
	if (file_token && file_token->type == TOKEN_WORD)
	{
		redir->file = strdup(file_token->value);
		*tokens = file_token->next;
	}
	else
	{
		redir->file = NULL;
		*tokens = (*tokens)->next;
	}
	redir->fd = -1;
	if (redir->type == TOKEN_HEREDOC)
		redir->delimiter = redir->file;
	else
		redir->delimiter = NULL;
	return (redir); 
}

void	attach_redirections(t_tree_node *node, t_redirection *redir)
{
	t_redirection	*current;

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
t_tree_node	*parse_command(t_token **tokens)
{
	t_tree_node		*node;
	t_tree_node		*current;
	t_tree_node		*subshell_node;
	t_redirection	*redirections;
	char			*value;
	t_token			*next;
	t_redirection	*new_redir;
	t_redirection	*last_redir;

	node = NULL;
	current = NULL;
	subshell_node = NULL;
	redirections = NULL;
	while (*tokens && ((*tokens)->type == TOKEN_WORD
			|| (*tokens)->type == TOKEN_WHITESPACE
			|| (*tokens)->type == TOKEN_SUBSHELL
			|| (*tokens)->type == TOKEN_REDIR_IN
			|| (*tokens)->type == TOKEN_REDIR_OUT
			|| (*tokens)->type == TOKEN_REDIR_APPEND
			|| (*tokens)->type == TOKEN_HEREDOC
			|| (*tokens)->type == TOKEN_ENV
			|| (*tokens)->type == TOKEN_SPECIAL_VAR))
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
		if ((*tokens)->type == TOKEN_REDIR_IN
			|| (*tokens)->type == TOKEN_REDIR_OUT
			|| (*tokens)->type == TOKEN_REDIR_APPEND
			|| (*tokens)->type == TOKEN_HEREDOC)
		{
			new_redir = parse_redirection(tokens);
			if (redirections == NULL)
			{
				redirections = new_redir;
			}
			else
			{
				last_redir = redirections;
				while (last_redir->next)
					last_redir = last_redir->next;
				last_redir->next = new_redir;
			}
			continue ;
		}
		if ((*tokens)->type == TOKEN_WORD)
		{
			while ((*tokens)->next && (*tokens)->next->type == TOKEN_WORD)
			{
				value = ft_strjoin((*tokens)->value, (*tokens)->next->value);
				free((*tokens)->value);
				(*tokens)->value = value;
				next = (*tokens)->next;
				(*tokens)->next = next->next;
				free(next);
			}
		}
		if (node == NULL)
		{
			node = create_tree_node(*tokens);
			current = node;
			if (redirections)
			{
				attach_redirections(node, redirections);
				redirections = NULL;
			}
			printf("value: %s, type: %u\n", current->token->value, current->token->type);
		}
		else
		{
			current->right = create_tree_node(*tokens);
			current = current->right;
		}
		*tokens = (*tokens)->next;
	}
	if (node && redirections)
		attach_redirections(node, redirections);
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
