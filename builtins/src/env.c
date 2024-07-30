/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 09:49:31 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/07/30 10:29:53 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../inc/builtins.h"

/**
 * create_env_dict - it will create(allocate)!!! a sort of a match of a python dictionary/list
 * that contains in each node in it an enviroment variable with as a pair of 
 * key value and return it to work with it while the whole running of the program
 * and it should be launched at the beginning of the program
 * @env: the 2d array of enviroment variables inherited from the previous shell
 * Return : on succes the linked list, on failure NULL
 */
t_env *create_env_dict(char **env)
{
    t_env *head;
    if (!env)
        return (NULL);
    head = NULL;
    while(*env)
    {
        append_node(&head, *env);
        env++;
    }
    return head;
}

/**
 * respond_to_env - it will respond to env call and print all the enviroment variables
 * @envp: the 2 array of inherited enviroment variables
 * Return: none
*/
int respond_to_env(t_env *the_whole_list)
{
    print_list(the_whole_list);
    return 1;
    // !!! this to be handled in case of a variable that doesn't conatain a value
}
