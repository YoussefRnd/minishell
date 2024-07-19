/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:14:46 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/07/19 13:29:16 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../inc/builtins.h"

void respond_to_cd(char *path, t_env **list)
{
    char buff[1024];
    if (access(path, X_OK) != -1)
    {
        if (chdir(path) != 0)
            perror("shiiih");
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
    respond_to_cd(av[1], &list);
}