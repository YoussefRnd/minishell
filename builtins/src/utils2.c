/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:18:11 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/09/14 15:54:17 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../exec/inc/execution.h"
#include "../../inc/minishell.h"
#include "../inc/builtins.h"

void	print_list(t_env *head)
{
	t_env	*current;

	current = head;
	while (current != NULL)
	{
		if (current->value)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
}

char	**allocate_array_env(int count)
{
	char	**array;

	array = malloc((count + 1) * sizeof(char *));
	if (array == NULL)
	{
		perror("Failed to allocate memory");
		return (NULL);
	}
	return (array);
}

char	*process_env_token(t_tree_node *current, t_env **env, bool exp)
{
	char	*result;

	result = NULL;
	if (!exp)
		result = ft_strdup(get_value(*env, current->token->value));
	return (result);
}

char	*process_it_token(t_tree_node *current, t_env **env, bool exp)
{
	char	*value;

	value = NULL;
	if (current->token->type == TOKEN_ENV)
		value = process_env_token(current, env, exp);
	else if (current->token->type == TOKEN_SPECIAL_VAR)
		value = ft_itoa(g_status);
	else
		value = ft_strdup(current->token->value);
	return (value);
}

void	fill_array(char **array, t_tree_node *root, t_env **env, bool exp)
{
	t_tree_node	*current;
	int			i;

	current = root;
	i = 0;
	while (current != NULL)
	{
		if (ft_strlen(current->token->value) > 0)
		{
			array[i] = process_it_token(current, env, exp);
			i++;
		}
		current = current->right;
	}
	array[i] = NULL;
}
