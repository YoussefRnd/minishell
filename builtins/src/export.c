/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:55:29 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/08/07 13:19:53 by hbrahimi         ###   ########.fr       */
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
    int in = dup(STDIN_FILENO);
	int out = dup(STDOUT_FILENO);
    char **args = traverse_right_and_collect_values(cmd->right, list, true);
    // printf("inside of export\n");
    if (!args){
        if (cmd->redirections)
            handle_redir(cmd->redirections);
        print_list_exp(*list);
    }
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
    dup2(in, STDIN_FILENO);
    dup2(out, STDOUT_FILENO);
    return (0);
    // we gotta handle failures
    // change the value if it got the same key
    // and free up memory
}
