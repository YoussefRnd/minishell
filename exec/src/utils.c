/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 09:43:36 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/07/26 12:29:44 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../parser/inc/parser.h"
#include "../inc/execution.h"

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

char *get_value(t_env *env, char *key) {
    t_env *current = env;
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }
    return NULL;
}

char **examine(t_tree_node *head, char *path)
{
    int count;
    t_tree_node *current;
    char **array;
    int i;

    current = head;
    count = count_nodes(current);
    array = (char **)malloc((count + 2) * sizeof(char *));
    if (array == NULL)
        return (NULL);

    // Set the first element to the path
    array[0] = ft_strdup(path);

    i = 1;
    current = head;
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

char	*ft_strcpy(char *dest, const char *src)
{
	char	*save;
	int		i;

	save = dest;
	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (save);
}

char	*ft_strcat(char *dest, const char *src)
{
	char	*rdest;
	int		i;

	rdest = dest;
	while (*dest)
	{
		dest++;
	}
	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (rdest);
}

// void dup_them()