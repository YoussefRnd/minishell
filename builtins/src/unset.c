/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:21:35 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/08/05 09:54:32 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../inc/builtins.h"

int	respond_to_unset(t_env **list, t_tree_node *cmd)
{
	char	**args;

	//TODO to be handeled: invalid identifiers
	args = traverse_right_and_collect_values(cmd->right, list, false);
	if (!args)
		return (1);
	else
		while (*args)
		{
			find_and_remove(list, *args);
			args++;
		}
	return (0);
}

void	find_and_remove(t_env **head_ref, char *key)
{
	t_env	*current;
	t_env	*previous;

	current = *head_ref;
	previous = NULL;
	if (current != NULL && ft_strcmp(current->key, key) == 0)
	{
		*head_ref = current->next; // Change head
		free(current->key);        // Free key
		free(current->value);      // Free value
		free(current);             // Free old head
		return ;
	}
	while (current != NULL && ft_strcmp(current->key, key) != 0)
	{
		previous = current;
		current = current->next;
	}
	if (current == NULL)
		return ;
	previous->next = current->next;
	free(current->key);   // Free key
	free(current->value); // Free value
	free(current);        // Free memory
}
