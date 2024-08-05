/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 22:51:39 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/08/05 23:17:19 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/builtins.h"

int respond_to_exit(t_tree_node *cmd_args, t_env **env)
{
    char **args = traverse_right_and_collect_values(cmd_args, env, false);
    if (args && args[1]){
        printf("too many arguments\n");
        return -1;
    }
    if (args && args[0])
        exit(ft_atoi(args[0]));
    else
        exit(status);
}