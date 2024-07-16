/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:55:29 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/07/16 15:17:52 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../inc/env.h"

/**
 * respond_to_export - respond to export call
 * @list: the enviroment variables
 * @args: the args of export
 * Return: none
*/
void respond_to_export(t_env *list, char **args)
{
    if (!args)
        print_list_exp(list);
    else
        while(*args)
        {
            append_node(&list, *args);
            args++;
        }
    // i gotta handle failures
}

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

