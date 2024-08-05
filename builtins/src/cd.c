/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 17:45:16 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/08/05 10:23:30 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../exec/inc/execution.h"
#include "../inc/builtins.h"

int	respond_to_cd(t_tree_node *cmd, t_env **env)
{
	char *directory;
	if (!cmd)
	{
		directory = get_value(*env, "HOME");
		if (!directory)
		{
			perror("HOME not set");
			return (-1);
		}
	}
	else
	{
		char **args = traverse_right_and_collect_values(cmd, env, false);
		directory = args[0];
	}
	char oldpwd[1024];
	char cwd[1024];
	 if (!getcwd(oldpwd, sizeof(oldpwd)))
    {
        perror("getcwd failed");
        return (-1);
    }
	if (chdir(directory))
	{
		perror("cd failed");
		return (-1);
	}
	if (!getcwd(cwd, sizeof(cwd)))
    {
        perror("getcwd failed");
        return (-1);
    }
	find_and_modify(env, "OLDPWD", oldpwd);
	find_and_modify(env, "PWD", cwd);
	return (0);
}
