/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:21:35 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/07/16 17:42:06 by hbrahimi         ###   ########.fr       */
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
void respond_to_unset(t_env **list, char **args)
{
    // to be handeled: invalid identifiers
    if (!args)
        return ;
    else
        while (*args)
        {
            find_and_remove(list, *args);
            args++;
        }       
}

void find_and_remove(t_env **list, char *key)
{
    t_env *current = *list;
    while(current)
    {
        if (!(ft_strcmp(key, current->key)))
        {
            
        }
    }
}