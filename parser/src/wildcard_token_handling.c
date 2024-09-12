/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_token_handling.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 19:08:07 by yboumlak          #+#    #+#             */
/*   Updated: 2024/09/12 19:08:13 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

t_token	*create_wildcard_token(char **matches, int i)
{
	t_token	*new_token;

	new_token = create_token(TOKEN_WORD, ft_strdup(matches[i]), NORMAL);
	if (new_token == NULL)
	{
		free_array(matches);
		return (NULL);
	}
	return (new_token);
}

void	create_wildcard_node(t_tree_node **node, t_tree_node **current,
		t_token *new_token)
{
	if (*node == NULL)
	{
		*node = create_tree_node(new_token);
		*current = *node;
	}
	else
	{
		(*current)->right = create_tree_node(new_token);
		*current = (*current)->right;
	}
	free_token(&new_token);
}

int	add_wildcard_token_to_tree(t_token **tokens, t_tree_node **node,
		t_tree_node **current)
{
	char	**matches;
	t_token	*new_token;
	int		i;

	matches = expand_wildcard((*tokens)->value);
	if (!matches)
		return (0);
	i = 0;
	while (matches[i])
	{
		new_token = create_wildcard_token(matches, i);
		if (new_token == NULL)
		{
			free_tree(node);
			return (1);
		}
		create_wildcard_node(node, current, new_token);
		i++;
	}
	free_array(matches);
	*tokens = (*tokens)->next;
	return (1);
}
