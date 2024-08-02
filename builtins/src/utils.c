/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 09:49:45 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/08/02 18:43:04 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../inc/builtins.h"
#include "../../exec/inc/execution.h"

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

void free_node(t_env *node) {
    free(node->value);
    free(node->key);
    free(node);
}

int update_node_if_key_matches(t_env *node, t_env *new_node) {
    if (ft_strcmp(node->key, new_node->key) == 0) {
        free(node->value);
        node->value = ft_strdup(new_node->value);
        free_node(new_node);
        return 1;
    }
    return 0;
}

void append_node(t_env **head, char *data) {
    t_env *new_node = malloc(sizeof(t_env));
    t_env *current;

    node_init(data, new_node);
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
    } else {
        current = *head;
        while (current->next != NULL) {
            if (update_node_if_key_matches(current, new_node)) {
                return;
            }
            current = current->next;
        }
        if (update_node_if_key_matches(current, new_node)) {
            return;
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
		if (ft_strlen(current->value) > 0)
        	printf("%s=%s\n", current->key, current->value);
        current = current->next;
    }
}
char **traverse_right_and_collect_values(t_tree_node *root, t_env **env, bool exp)
{
    // First, count the number of nodes in the tree
    int count = count_nodes(root);
	if (!count)
		return NULL;

    // Allocate the array
    char **array = malloc((count + 1) * sizeof(char *));
    if (array == NULL)
    {
        perror("Failed to allocate memory");
        return NULL;
    }

    // Traverse the tree and collect the values
    t_tree_node *current = root;
    int i = 0;
    while (current != NULL)
    {
        if (ft_strlen(current->token->value) > 0)
        {
			if (current->token->type == TOKEN_ENV){
				printf("expanding inside of a builtin\n");
				// TODO check if it's an empty string or if it exists at the first place
                char **splitted = split_it(current->token->value);
				if (!exp)
                    array[i] = get_value(*env, splitted[0]);
                else{
                    char *this = ft_strjoin(get_value(*env, splitted[0]), "=");
                    array[i] = ft_strjoin(this, splitted[1]);
                    free(this);
                }
				printf("splitted[0]: %s | splitted[1]: %s | array[i]: %s\n", splitted[0], splitted[1], array[i]);
                free(splitted[0]);
                free(splitted[1]);
                free(splitted);
			}
            else
				array[i] = current->token->value;
            i++;
        }
        current = current->right;
    }

    // Null-terminate the array
    array[i] = NULL;

    return array;
}

int node_exists(t_env **head_ref, char *key)
{
    t_env* current = *head_ref;

    while (current != NULL)
    {
        if (ft_strcmp(current->key, key) == 0)
        {
            return 1; // Node exists
        }
        current = current->next;
    }
    return 0; // Node does not exist
}
void modify_node(t_env **head_ref, char *key, char *new_value)
{
    t_env* current = *head_ref;

    while (current != NULL)
    {
        if (ft_strcmp(current->key, key) == 0)
        {
            free(current->value); // Free the old value
            current->value = strdup(new_value); // Assign the new value
            return;
        }
        current = current->next;
    }
}