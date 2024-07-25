/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:26:23 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/07/25 10:09:19 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../inc/minishell.h"
#include "../inc/execution.h"

void _execute(t_tree_node *tree, t_env *env)
{
    if(tree->token->type == TOKEN_WORD){
        cmd_execute(tree, env);
        return ;
    }
    // else if (tree->token->type == TOKEN_PIPE){
    //     similar_popen(tree);
    // }
}

void cmd_execute(t_tree_node *cmd, t_env *envps)
{
    // printf("cmd: %s\n", cmd->token->value);
    // printf("args: %s\n", cmd->right->token->value);
    // i gotta find the path that am a give to execve
    char **path_dirs = ft_split(find_and_return_value(envps, "PATH"));
    char *path = find_path(cmd->token->value, path_dirs);
    if (!path)
    {
        perror("command not found");
        return ;
    }
    // then iterate over the tree to get the set of args
    char **args = examine(cmd->right);
    char **env = to_arr(envps);
    execve(path, args, env);
    perror("command failed")
}

char	*find_path(char *file, char **arr)
{
	int		i;
	char	*path_buffer;

	if (!arr || !*arr)
		exit(EXIT_FAILURE);
	i = 0;
	path_buffer = NULL;
	while (arr[i])
	{
		if (access(file, X_OK | F_OK) == 0)
			return (ft_free(arr), ft_strdup(file));
		if (path_buffer)
			free_n_set_to_null(&path_buffer);
		path_buffer = malloc(ft_strlen(arr[i]) + ft_strlen(file) + 2);
		ft_strcpy(path_buffer, arr[i]);
		ft_strcat(path_buffer, "/");
		ft_strcat(path_buffer, file);
		ft_strcat(path_buffer, "\0");
		if (access(path_buffer, X_OK) == 0)
			return (ft_free(arr), path_buffer);
		i++;
	}
	if (path_buffer)
		free(path_buffer);
	return (perror(file), ft_free(arr), NULL);
}
