/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:16:43 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/09/12 17:21:43 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../exec/inc/execution.h"
#include "../../inc/minishell.h"
#include "../inc/builtins.h"

char	**traverse_right_and_collect_values(t_tree_node *root, t_env **env,
		bool exp)
{
	int		count;
	char	**array;

	count = count_nodes(root);
	if (!count)
		return (NULL);
	array = allocate_array_env(count);
	if (array == NULL)
		return (NULL);
	fill_array(array, root, env, exp);
	return (array);
}

int	node_exists(t_env **head_ref, char *key)
{
	t_env	*current;

	current = *head_ref;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			return (1);
		}
		current = current->next;
	}
	return (0);
}

void	find_and_modify(t_env **head_ref, char *key, char *new_value)
{
	t_env	*current;

	current = *head_ref;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = ft_strdup(new_value);
			return ;
		}
		current = current->next;
	}
}

int	count_nodes_env(t_env *head)
{
	int		count;
	t_env	*current;

	count = 0;
	current = head;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	return (count);
}

void	free_env_list(t_env **head_ref)
{
	t_env	*current;
	t_env	*next;

	current = *head_ref;
	while (current != NULL)
	{
		next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
	*head_ref = NULL;
}
