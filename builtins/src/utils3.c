/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:20:06 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/09/15 13:49:42 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../exec/inc/execution.h"
#include "../../inc/minishell.h"
#include "../inc/builtins.h"

void	free_node(t_env **node)
{
	safe_free(&(*node)->value);
	safe_free(&(*node)->key);
	free(*node);
	*node = NULL;
}

int	update_node_if_key_matches(t_env *node, t_env *new_node)
{
	if (ft_strcmp(node->key, new_node->key) == 0)
	{
		if (node->value && !new_node->value)
		{
			free_node(&new_node);
			return (1);
		}
		free(node->value);
		node->value = ft_strdup(new_node->value);
		free_node(&new_node);
		return (1);
	}
	return (0);
}

void	append_node(t_env **head, char *data)
{
	t_env	*new_node;
	t_env	*current;

	new_node = malloc(sizeof(t_env));
	if (!node_init(data, new_node))
	{
		free(new_node);
		return ;
	}
	new_node->next = NULL;
	if (*head == NULL)
		*head = new_node;
	else
	{
		current = *head;
		while (current->next != NULL)
		{
			if (update_node_if_key_matches(current, new_node))
				return ;
			current = current->next;
		}
		if (update_node_if_key_matches(current, new_node))
			return ;
		current->next = new_node;
	}
}

int	is_valid_env_var_name(const char *key)
{
	int	i;

	i = 1;
	if (key == NULL || *key == '\0')
		return (0);
	if (!ft_isalpha((unsigned char)key[0]) && key[0] != '_')
		return (0);
	while (key[i] != '\0')
	{
		if (!ft_isalnum((unsigned char)key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	node_init(char *str, t_env *node)
{
	char	**splitted;

	splitted = split_it(str);
	if (is_valid_env_var_name(splitted[0]))
	{
		node->key = ft_strdup(splitted[0]);
		node->value = ft_strdup(splitted[1]);
		free_array(splitted);
	}
	else
	{
		printf("invalid key\n");
		free_array(splitted);
		return (0);
	}
	return (1);
}
