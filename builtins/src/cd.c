/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 17:45:16 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/09/13 21:53:04 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../exec/inc/execution.h"
#include "../inc/builtins.h"

char	*get_directory(t_tree_node *cmd, t_env **env)
{
	char	*directory;
	char	**args;

	args = NULL;
	if (!cmd)
	{
		directory = find_and_return_value(*env, "HOME");
		if (!directory)
		{
			perror("HOME not set");
			return (NULL);
		}
	}
	else
	{
		args = traverse_right_and_collect_values(cmd, env, false);
		directory = ft_strdup(args[0]);
	}
	free_array(args);
	return (directory);
}

int	change_directory(char *directory)
{
	if (chdir(directory))
	{
		perror("cd failed");
		return (-1);
	}
	return (0);
}

int	update_pwd(t_env **env, char *oldpwd)
{
	char	cwd[1024];

	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("getcwd failed");
		return (-1);
	}
	find_and_modify(env, "OLDPWD", oldpwd);
	find_and_modify(env, "PWD", cwd);
	return (0);
}

int	free_n_return(char **directory)
{
	safe_free(directory);
	return (1);
}

int	respond_to_cd(t_tree_node *cmd, t_env **env)
{
	char	oldpwd[1024];
	char	*directory;

	if (!getcwd(oldpwd, sizeof(oldpwd)))
	{
		perror("getcwd failed");
		return (-1);
	}
	directory = get_directory(cmd, env);
	if (!directory)
		return (free_n_return(&directory));
	if (change_directory(directory) == -1)
		return (free_n_return(&directory));
	if (update_pwd(env, oldpwd) == -1)
		return (free_n_return(&directory));
	safe_free(&directory);
	return (0);
}
