/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 09:43:36 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/07/24 11:41:35 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char* find_and_return_value(t_env *head_ref, char *key)
{
    t_env* current = head_ref;

    // Search for the key
    while (current != NULL)
    {
        if (ft_strcmp(current->key, key) == 0)
        {
            // Found the key, return a copy of the value
            return ft_strdup(current->value);
        }
        current = current->next;
    }

    // If the key was not present in the linked list
    return NULL;
}

char	**examine(t_tree *head)
{
	int		count;
	t_tree	*current;
	char	**array;
	int		i;

	current = head;
	count = count_nodes(current);
	array = (char **)malloc((count + 1) * sizeof(char *));
	if (array == NULL)
		return (NULL);
	i = 0;
	current = *head;
	while (current != NULL)
	{
		if (ft_strlen(current->token->value) > 0)
		{
			array[i] = current->token->value;
			i++;
		}
		current = current->right;
	}
	array[i] = NULL;
	return (array);
}

int	count_nodes(t_tree *current)
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

char **to_arr(t_env *head)
{
    // First, count the number of nodes in the linked list
    int count = 0;
    t_env* current = head;
    while (current != NULL)
    {
        count++;
        current = current->next;
    }

    // Allocate memory for the array
    char** array = malloc((count + 1) * sizeof(char*));
    if (array == NULL)
    {
        return NULL; // Failed to allocate memory
    }

    // Convert each node to a string and store it in the array
    current = head;
    for (int i = 0; i < count; i++)
    {
        // Allocate memory for the string
        array[i] = malloc(strlen(current->key) + strlen(current->value) + 2);
        if (array[i] == NULL)
        {
            return NULL; // Failed to allocate memory
        }

        // Create the string
        strcpy(array[i], current->key);
        strcat(array[i], "=");
        strcat(array[i], current->value);

        current = current->next;
    }

    // The last element of the array should be NULL
    array[count] = NULL;

    return array;
}
