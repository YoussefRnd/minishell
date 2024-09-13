/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:11:11 by yboumlak          #+#    #+#             */
/*   Updated: 2024/09/13 23:44:30 by yboumlak         ###   ########.fr       */
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
		if (current->file != NULL && current->type != TOKEN_HEREDOC)
		{
			free(current->file);
			current->file = NULL;
		}
		if (current->delimiter != NULL)
		{
			free(current->delimiter);
			current->delimiter = NULL;
		}
		*redirection = next;
		if (current != NULL)
		{
			free(current);
			current = NULL;
		}
	}
	*redirection = NULL;
}

void	free_tree(t_tree_node **node)
{
	if (*node == NULL)
		return ;
	free_tree(&(*node)->left);
	(*node)->left = NULL;
	free_tree(&(*node)->right);
	(*node)->right = NULL;
	if ((*node)->redirections != NULL)
	{
		free_redirections(&(*node)->redirections);
		(*node)->redirections = NULL;
	}
	if ((*node)->token != NULL)
	{
		free_token(&(*node)->token);
		(*node)->token = NULL;
	}
	free(*node);
	*node = NULL;
}

char	**free_wildcards_on_error(char **matches, DIR *dir)
{
	if (dir)
		closedir(dir);
	if (matches)
		free_array(matches);
	return (NULL);
}
