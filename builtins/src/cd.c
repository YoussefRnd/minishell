/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:14:46 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/07/20 13:26:21 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../inc/builtins.h"

void respond_to_cd(char *path, t_env **list)
{
    char buff[1024];
    if (access(path, F_OK) != -1)
    {
        printf("inside\n");
        // if (chdir(path) != 0)
        //     perror("shiiih");
        chdir(path);
        if (node_exists(list, "OLDPWD"))
            modify_node(list, "OLDPWD", getcwd(buff, 1024));
        if (node_exists(list, "PWD"))
            modify_node(list, "PWD", path);
    }
    else
        perror("shhhih");
}

int main(int ac, char **av, char **envp)
{
    t_env *list = create_env_dict(envp);
    char *path = "/Users/hbrahimi/";
    respond_to_cd(path, &list);
}