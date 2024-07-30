/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:11:11 by yboumlak          #+#    #+#             */
/*   Updated: 2024/07/29 19:54:34 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	free_redirections(t_redirection **redirection)
{
	t_redirection	*next;
	t_redirection	*current;

	while (*redirection)
	{
		current = *redirection;
		next = current->next;
		free(current->file);
		free(current->delimiter);
		free(current);
		*redirection = next;
	}
	*redirection = NULL;
}

void	free_tree(t_tree_node **node)
{
	if (*node == NULL)
		return ;
	free_tree(&(*node)->left);
	free_tree(&(*node)->right);
	free_redirections(&(*node)->redirections);
	free_tokens(&(*node)->token);
	*node = NULL;
}
