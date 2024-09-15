/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:27:02 by yboumlak          #+#    #+#             */
/*   Updated: 2024/09/15 22:01:26 by hbrahimi         ###   ########.fr       */
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
