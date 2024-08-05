/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:55:29 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/08/05 23:07:11 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../inc/builtins.h"

// TODO the value
void print_list_exp(t_env *list)
{
    t_env *current = list;

    while (current != NULL)
    {
        if (current->value == NULL)
        {
            printf("declare -x %s\n", current->key);
        }
        else
        {
            printf("declare -x %s=\"%s\"\n", current->key, current->value);
        }
        current = current->next;
    }
}

int respond_to_export(t_env **list, t_tree_node *cmd)
{
    char **args = traverse_right_and_collect_values(cmd->right, list, true);
    // printf("inside of export\n");
    if (!args)
        print_list_exp(*list);
    else
    {
        while(*args)
        {
            //TODO check the validity of arguments
            // check the key for validity
            // 
            append_node(list, *args);
            // printf("the argument:%s\n", *args);
            args++;
        }
    }
    return (0);
    // we gotta handle failures
    // change the value if it got the same key
    // and free up memory
}
