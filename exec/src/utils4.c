/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:27:06 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/09/12 17:27:37 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../parser/inc/parser.h"
#include "../inc/execution.h"

char	**examine(t_tree_node *head, char *path, t_env *env)
{
	t_tree_node	*current;
	char		**array;
	int			i;

	current = head;
	array = allocate_array(current, path);
	if (array == NULL)
		return (NULL);
	i = 1;
	while (current != NULL)
	{
		if (ft_strlen(current->token->value) > 0)
		{
			process_tok(current, env);
			array[i] = current->token->value;
			i++;
		}
		current = current->right;
	}
	array[i] = NULL;
	return (array);
}

int	count_nodes(t_tree_node *current)
{
	int	count;

	count = 0;
	while (current != NULL)
	{
		count++;
		current = current->right;
	}
	return (count);
}

char	**to_arr(t_env *head)
{
	int		count;
	t_env	*current;
	char	**array;
	int		i;

	count = count_nodes_env(head);
	i = -1;
	current = head;
	array = malloc((count + 1) * sizeof(char *));
	if (array == NULL)
		return (NULL);
	current = head;
	while (++i < count)
	{
		array[i] = malloc(strlen(current->key) + strlen(current->value) + 2);
		if (array[i] == NULL)
			return (NULL);
		ft_strcpy(array[i], current->key);
		ft_strcat(array[i], "=");
		ft_strcat(array[i], current->value);
		current = current->next;
	}
	array[count] = NULL;
	return (array);
}

void	free_n_set_to_null(char **v)
{
	free(*v);
	*v = NULL;
}

void	ft_free(char **splitted)
{
	int	c;

	c = 0;
	while (splitted[c])
	{
		free(splitted[c]);
		c++;
	}
	free(splitted);
	return ;
}
