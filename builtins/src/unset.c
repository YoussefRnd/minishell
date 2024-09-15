/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:21:35 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/09/10 15:28:50 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../inc/builtins.h"

int	respond_to_unset(t_env **list, t_tree_node *cmd)
{
	char	**args;
	int		i;

	i = 0;
	args = traverse_right_and_collect_values(cmd->right, list, false);
	if (!args)
		return (1);
	else
	{
		while (args[i])
		{
			if (!is_valid_env_var_name(args[i]))
			{
				printf("invalid identifier\n");
				i++;
				continue ;
			}
			find_and_remove(list, args[i]);
			i++;
		}
	}
	free_array(args);
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
		*head_ref = current->next;
		safe_free(&current->key);
		safe_free(&current->value);
		free(current);
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
	safe_free(&current->key);
	safe_free(&current->value);
	free(current);
}
