/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:55:29 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/07/19 10:21:01 by hbrahimi         ###   ########.fr       */
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
void respond_to_export(t_env **list, char **args)
{
    if (!args)
        print_list_exp(*list);
    else
        while(*args)
        {
            append_node(list, *args);
            args++;
        }
    // i gotta handle failures
}

// int main(int ac, char **av, char **envp)
// {
//     t_env *list = create_env_dict(envp);
//     char *args[3] = {"key=value", "noice", NULL};
//     respond_to_export(&list, args);
//     print_list(list);
// }
