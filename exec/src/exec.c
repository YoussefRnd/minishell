/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:26:23 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/09/14 18:18:31 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../builtins/inc/builtins.h"
#include "../../inc/minishell.h"
#include "../inc/execution.h"

void	_execute(t_tree_node *tree, t_env **env, bool *forked)
{
	if (!tree)
		return ;
	if (tree->token->type == TOKEN_WORD)
		words_deal(tree, env, forked);
	else if (tree->token->type == TOKEN_PIPE)
		pipes_deal(tree, env, forked);
	else if (tree->token->type == TOKEN_AND || tree->token->type == TOKEN_OR)
		operators_deal(tree, env, forked);
	else if (tree->token->type == TOKEN_SUBSHELL)
		subshells_deal(tree, env, forked);
	else if (tree->token->type == TOKEN_ENV)
		envs_deal(tree, env, forked);
	else if (tree->token->type == TOKEN_SPECIAL_VAR)
	{
		free(tree->token->value);
		tree->token->value = ft_itoa(g_status);
		tree->token->type = TOKEN_WORD;
		_execute(tree, env, forked);
	}
	else if (tree->token->type == TOKEN_BUILTIN)
	{
		g_status = respond_to_b(tree, env);
		return ;
	}
}

void	operators_deal(t_tree_node *tree, t_env **env, bool *forked)
{
	if (tree->left)
		_execute(tree->left, env, forked);
	else
		return ;
	if (g_status == 0 && tree->token->type == TOKEN_AND)
		_execute(tree->right, env, forked);
	else if (g_status != 0 && tree->token->type == TOKEN_OR)
		_execute(tree->right, env, forked);
}

void	cmd_execute(t_tree_node *cmd, t_env **envps)
{
	char	**path_dirs;
	char	*holder;
	char	*path;
	char	**args;
	char	**env;

	if (cmd->redirections)
	{
		if (handle_redir(cmd->redirections))
			exit(EXIT_FAILURE);
	}
	holder = find_and_return_value(*envps, "PATH");
	path_dirs = ft_split(holder, ':');
	safe_free(&holder);
	if (its_a_directory(cmd->token->value))
		exit(126);
	path = find_path(cmd->token->value, path_dirs);
	if (!path)
		exit(127);
	args = examine(cmd->right, path, *envps);
	env = to_arr(*envps);
	free(cmd->token->value);
	execve(path, args, env);
	perror("command failed");
	exit(EXIT_FAILURE);
}

char	*check_x(char *file)
{
	if (access(file, X_OK | F_OK) == 0)
		return (ft_strdup(file));
	exit(EXIT_FAILURE);
}

char	*find_path(char *file, char **arr)
{
	int		i;
	char	*path_buffer;

	if (!arr || !*arr)
		return (check_x(file));
	i = 0;
	path_buffer = NULL;
	while (arr[i])
	{
		if (path_buffer)
			free_n_set_to_null(&path_buffer);
		path_buffer = malloc(ft_strlen(arr[i]) + ft_strlen(file) + 2);
		ft_strcpy(path_buffer, arr[i]);
		ft_strcat(path_buffer, "/");
		ft_strcat(path_buffer, file);
		if (access(path_buffer, X_OK) == 0)
			return (ft_free(arr), path_buffer);
		i++;
	}
	if (path_buffer)
		free(path_buffer);
	if (access(file, X_OK | F_OK) == 0)
		return (ft_free(arr), ft_strdup(file));
	return (perror(file), ft_free(arr), NULL);
}
