/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:21:35 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/08/01 17:13:59 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../inc/builtins.h"

/**
 * respond_to_unset - it will remove all the nodes that matches the arguments specified
 * from the list of enviroment variables
 * @list: wich is the list that i've talked about
 * @args: the args that should be removed
*/
int respond_to_unset(t_env **list, t_tree_node *cmd)
{
    // to be handeled: invalid identifiers
    char **args = traverse_right_and_collect_values(cmd->right, list);
    if (!args)
        return 1;
    else
        while (*args)
        {
            find_and_remove(list, *args);
            args++;
        }
    return 0;       
}

void find_and_remove(t_env **head_ref, char *key)
{
    t_env* current = *head_ref;
    t_env* previous = NULL;

    // Check if the key is in the head node
    if (current != NULL && strcmp(current->key, key) == 0)
    {
        *head_ref = current->next; // Change head
        free(current->key); // Free key
        free(current->value); // Free value
        free(current); // Free old head
        return;
    }

    // Search for the key
    while (current != NULL && strcmp(current->key, key) != 0)
    {
        previous = current;
        current = current->next;
    }

    // If the key was not present in the linked list
    if (current == NULL) return;

    // Unlink the node from the linked list
    previous->next = current->next;

    free(current->key); // Free key
    free(current->value); // Free value
    free(current); // Free memory
}

// int main(int ac, char **av, char **envp)
// {
//     t_env *list = create_env_dict(envp);
//     print_list(list);
//     char *args[3] = {"bla", "tada", NULL};
//     respond_to_unset(&list, args);
//     printf("___________________\n");
//     print_list(list);
// }