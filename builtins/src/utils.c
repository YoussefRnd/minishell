/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 09:49:45 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/07/16 12:32:44 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../inc/env.h"

/**
 * split_it - it will split the string passed to it on half
 * @str: the str to be splitted
 * Return: an allocated !!! array of two strings
 */
char	**split_it(char *str)
{
	char	*equal_pos;
	int		key_len;
	int		value_len;
	char	**that;
	int		i;

	i = 0;
	key_len = 0;
	value_len = 0;
	if (!str)
		return (NULL);
	that = ft_calloc(sizeof(char *), 3);
	while (str[i] && str[i] != '=')
	{
		i++;
		key_len++;
	}
	while (str[i])
	{
		i++;
		value_len++;
	}
	that[0] = ft_substr(str, 0, key_len);
	that[1] = ft_substr(str, key_len + 1, value_len);
	that[2] = NULL;
	return (that);
}

/**
 * @brief Appends a new node to the end of a linked list.
 *
 * This function creates a new node with the given data, initializes it using the node_init function,
 * and appends it to the end of the linked list pointed to by head. If the linked list is empty (i.e., *head is NULL),
 * the new node becomes the head of the list.
 *
 * @param head Double pointer to the head of the linked list. If *head is NULL, the list is empty.
 * @param data Pointer to the data to be stored in the new node. The data is copied into the new node using the node_init function.
 *
 * @return void
 */
void	append_node(t_env **head, char *data)
{
	t_env	*new_node;
	t_env	*current;

	new_node = malloc(sizeof(t_env));
	node_init(data, new_node);
	new_node->next = NULL;
	if (*head == NULL)
	{
		*head = new_node;
	}
	else
	{
		current = *head;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new_node;
	}
}

/**
 * node_init - it will fill the right
 * formations of each env var in a node
 * @str: str is supposed to be the whole env variable
 * @node: is a node in the linked list
 */
void node_init(char *str, t_env *node)
{
    char **splitted;

    splitted = split_it(str);
    node->key = splitted[0];
    node->value = splitted[1];
}

/**
 * print_list - as it's name says
 * @head - as it's name says
 * Return: none
*/
void print_list(t_env *head)
{
    t_env *current = head;

    while (current != NULL) {
        printf("%s=%s\n", current->key, current->value);
        current = current->next;
    }
}