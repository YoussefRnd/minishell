/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:27:02 by yboumlak          #+#    #+#             */
/*   Updated: 2024/09/12 17:11:50 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

t_token	*copy_token(t_token *original)
{
	t_token	*copy;

	copy = malloc(sizeof(t_token));
	if (copy == NULL)
		return (NULL);
	copy->type = original->type;
	copy->value = ft_strdup(original->value);
	if (copy->value == NULL)
	{
		free(copy);
		return (NULL);
	}
	copy->next = NULL;
	copy->subtokens = NULL;
	copy->state = original->state;
	copy->is_atached = original->is_atached;
	return (copy);
}

t_tree_node	*create_tree_node(t_token *token)
{
	t_tree_node	*node;

	node = malloc(sizeof(t_tree_node));
	if (token != NULL)
		node->token = copy_token(token);
	else
		node->token = NULL;
	node->left = NULL;
	node->right = NULL;
	node->redirections = NULL;
	return (node);
}

// t_tree_node	*parse_command(t_token **tokens)
// {
// 	t_tree_node		*node;
// 	t_tree_node		*current;
// 	t_tree_node		*subshell_node;
// 	t_redirection	*redirections;
// 	char			*value;
// 	t_token			*next;
// 	t_redirection	*new_redir;
// 	t_redirection	*last_redir;
// 	char			**matches;
// 	t_token			*new_token;
// 	int				i;

// 	node = NULL;
// 	current = NULL;
// 	subshell_node = NULL;
// 	redirections = NULL;
// 	while (*tokens && ((*tokens)->type != TOKEN_EOF
// 			&& (*tokens)->type != TOKEN_PIPE && (*tokens)->type != TOKEN_AND
// 			&& (*tokens)->type != TOKEN_OR))
// 	{
// 		if (((*tokens)->type == TOKEN_ENV && (*tokens)->next
// 				&& (*tokens)->next->type != TOKEN_WHITESPACE
// 				&& (*tokens)->next->type != TOKEN_EOF) || ((*tokens)->next
// 				&& (*tokens)->next->type == TOKEN_ENV))
// 		{
// 			(*tokens)->is_atached = true;
// 		}
// 		if ((*tokens)->type == TOKEN_WHITESPACE
// 			|| (*tokens)->type == TOKEN_EMPTY)
// 		{
// 			*tokens = (*tokens)->next;
// 			continue ;
// 		}
// 		if ((*tokens)->type == TOKEN_SUBSHELL)
// 		{
// 			subshell_node = parse_subshell(tokens);
// 			if (node == NULL)
// 			{
// 				node = subshell_node;
// 				current = node;
// 			}
// 			else
// 			{
// 				current->right = subshell_node;
// 				current = current->right;
// 			}
// 			continue ;
// 		}
// 		if ((*tokens)->type == TOKEN_REDIR_IN
// 			|| (*tokens)->type == TOKEN_REDIR_OUT
// 			|| (*tokens)->type == TOKEN_REDIR_APPEND
// 			|| (*tokens)->type == TOKEN_HEREDOC)
// 		{
// 			new_redir = parse_redirection(tokens);
// 			if (new_redir == NULL)
// 			{
// 				free_tree(&node);
// 				return (NULL);
// 			}
// 			if (redirections == NULL)
// 				redirections = new_redir;
// 			else
// 			{
// 				last_redir = redirections;
// 				while (last_redir->next)
// 					last_redir = last_redir->next;
// 				last_redir->next = new_redir;
// 			}
// 			continue ;
// 		}
// 		if ((*tokens)->type == TOKEN_WORD || (*tokens)->type == TOKEN_ERROR
// 			|| (*tokens)->type == TOKEN_BUILTIN
// 			|| (*tokens)->type == TOKEN_WILDCARD)
// 		{
// 			while ((*tokens)->next && ((*tokens)->next->type == TOKEN_WORD
// 					|| (*tokens)->next->type == TOKEN_WILDCARD))
// 			{
// 				value = ft_strjoin((*tokens)->value, (*tokens)->next->value);
// 				free((*tokens)->value);
// 				(*tokens)->value = value;
// 				if ((*tokens)->next->type == TOKEN_WILDCARD)
// 					(*tokens)->type = TOKEN_WILDCARD;
// 				next = (*tokens)->next;
// 				(*tokens)->next = next->next;
// 				free(next);
// 			}
// 		}
// 		if ((*tokens)->type == TOKEN_WILDCARD)
// 		{
// 			matches = expand_wildcard((*tokens)->value);
// 			if (matches)
// 			{
// 				i = 0;
// 				while (matches[i])
// 				{
// 					new_token = create_token(TOKEN_WORD, ft_strdup(matches[i]),
// 							NORMAL);
// 					if (new_token == NULL)
// 					{
// 						free_array(matches);
// 						free_tree(&node);
// 						return (NULL);
// 					}
// 					if (node == NULL)
// 					{
// 						node = create_tree_node(new_token);
// 						free_token(&new_token);
// 						if (node == NULL)
// 						{
// 							free_token(&new_token);
// 							free_array(matches);
// 							return (NULL);
// 						}
// 						current = node;
// 					}
// 					else
// 					{
// 						current->right = create_tree_node(new_token);
// 						free_token(&new_token);
// 						if (current->right == NULL)
// 						{
// 							free_token(&new_token);
// 							free_array(matches);
// 							free_tree(&node);
// 							return (NULL);
// 						}
// 						current = current->right;
// 					}
// 					i++;
// 				}
// 				free_array(matches);
// 				*tokens = (*tokens)->next;
// 				continue ;
// 			}
// 		}
// 		if (node == NULL)
// 		{
// 			node = create_tree_node(*tokens);
// 			current = node;
// 			if (redirections)
// 			{
// 				attach_redirections(node, redirections);
// 				redirections = NULL;
// 			}
// 		}
// 		else
// 		{
// 			current->right = create_tree_node(*tokens);
// 			current = current->right;
// 		}
// 		*tokens = (*tokens)->next;
// 	}
// 	if (node && redirections)
// 		attach_redirections(node, redirections);
// 	return (node);
// }

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
		printf("%sFile descriptor: %d\n", indent, redirection->fd);
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
		printf("%s, %u, %d\n", node->token->value, node->token->type,
			node->token->is_atached);
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
