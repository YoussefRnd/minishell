/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 10:37:11 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/08/02 18:36:59 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../inc/builtins.h"

int respond_to_echo(t_tree_node *tree, t_env **env)
{
    bool flag = false;
    int i = 0;
    char **args = traverse_right_and_collect_values(tree->right, env, false);
    if (!args)
        printf("\n");
    else{
        while (args[i] && (ft_strcmp(args[i], "-n") == 0))
        {
            flag = true;
            i++;
        }
        while(args[i])
        {
            
            printf("%s", args[i]);
            i++;
            if (args[i])
                printf(" ");
        }
        if (!flag)
            printf("\n");
    }
    return 0;
}