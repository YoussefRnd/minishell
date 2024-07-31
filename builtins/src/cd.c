/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 17:45:16 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/07/31 18:50:14 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/builtins.h"
#include "../../exec/inc/execution.h"

int respond_to_cd(t_tree_node *cmd, t_env **env)
{
    // what i wanna do is if thre's no argument i gotta get back to home
    // and if not i will execute it just by chdir
    // i am willing to do this by
    // first of all check if there is a directory provided
    // if so i gotta provide it through get_value of the home
    // then i'll execute it
    //
    char *directory;
    if (!cmd){
        directory = get_value(*env, "HOME");
        if (!directory){
            perror("HOME not set");
            return (-1);
        }
    }
    else
        directory = cmd->token->value;
    if (chdir(directory)){
        perror("cd failed");
        return (-1);
    }
    return 0;
}