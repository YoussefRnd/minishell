/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:27:02 by yboumlak          #+#    #+#             */
/*   Updated: 2024/09/13 13:07:59 by yboumlak         ###   ########.fr       */
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
