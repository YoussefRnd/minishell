/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:55:29 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/08/02 18:36:39 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../inc/builtins.h"


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
/**
 * respond_to_export - respond to export call
 * @list: the enviroment variables
 * @args: the args of export
 * Return: none
*/
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

// int main(int ac, char **av, char **envp)
// {
//     t_env *list = create_env_dict(envp);
//     char *args[3] = {"key=value", "noice", NULL};
//     respond_to_export(&list, args);
//     print_list(list);
// }
