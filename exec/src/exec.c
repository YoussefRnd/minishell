/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:26:23 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/08/07 01:53:14 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../builtins/inc/builtins.h"
#include "../../inc/minishell.h"
#include "../inc/execution.h"

// TODO check why it stopped working when i call it again
// TODO protect forking
void	_execute(t_tree_node *tree, t_env **env, bool *forked)
{
	pid_t	pid;
	int		substatus;
	int		pfd[2];
	char	*value;

	pid_t pidl, pidr = 0;
	// int status2;
	if (!tree)
		return ;
	if (tree->token->type == TOKEN_WORD)
	{
		signal(SIGINT, SIG_IGN);
		pid = fork();
		if (pid == 0)
		{
			signal_handler_in_c();
			cmd_execute(tree, env);
		}
		else
		{
			wait(&status);
			handle_exit_status();
			if (*forked)
				exit(status);
			// ? idk maybe i gotta add + 128
		}
	}
	else if (tree->token->type == TOKEN_PIPE)
	{
		if (pipe(pfd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		*forked = true;
		signal(SIGINT, SIG_IGN);
		pidl = fork();
		if (!pidl)
		{
			close(pfd[0]);
			dup2(pfd[1], STDOUT_FILENO);
			_execute(tree->left, env, forked);
			exit(EXIT_SUCCESS);
		}
		if (pidl)
			pidr = fork();
		if (!pidr)
		{
			close(pfd[1]);
			dup2(pfd[0], STDIN_FILENO);
			_execute(tree->right, env, forked);
			exit(status);
		}
		close(pfd[0]);
		close(pfd[1]);
		// TODO to change
		waitpid(pidl, &substatus, 0);
		waitpid(pidr, &status, 0);
		handle_exit_status();
	}
	else if (tree->token->type == TOKEN_AND || tree->token->type == TOKEN_OR)
		operators_deal(tree, env, forked);
	else if (tree->token->type == TOKEN_SUBSHELL)
	{
		*forked = true;
		signal(SIGINT, SIG_IGN);
		pid = fork();
		if (!pid)
			_execute(tree->left, env, forked);
		else
		{
			wait(&status);
			handle_exit_status();
		}
	}
	// TO WORK ON LATER 7ITASH HAD L9LAWI M3NKSH
	else if (tree->token->type == TOKEN_ENV)
	{
		value = get_value(*env, tree->token->value);
		if (value)
		{
			free(tree->token->value);
			tree->token->value = ft_strdup(value);
			tree->token->type = TOKEN_WORD;
			_execute(tree, env, forked);
		}
	}
	else if (tree->token->type == TOKEN_BUILTIN)
	{
		status = respond_to_b(tree, env);
		return ;
	}
}

void	operators_deal(t_tree_node *tree, t_env **env, bool *forked)
{
	int	exit_status;

	if (tree->left)
		_execute(tree->left, env, forked);
	else
		return ;
	if (WIFEXITED(status))
	{
		exit_status = WEXITSTATUS(status);
		if (tree->right)
		{
			if (exit_status == 0 && tree->token->type == TOKEN_AND)
				_execute(tree->right, env, forked);
			else if (exit_status != 0 && tree->token->type == TOKEN_OR)
				_execute(tree->right, env, forked);
		}
	}
}

void	cmd_execute(t_tree_node *cmd, t_env **envps)
{
	char			**path_dirs;
	char			*path;
	char			**args;
	char			**env;

	if (cmd->redirections)
		handle_redir(cmd->redirections);
	path_dirs = ft_split(find_and_return_value(*envps, "PATH"), ':');
	path = find_path(cmd->token->value, path_dirs);
	if (!path)
		exit(127);
	args = examine(cmd->right, path, *envps);
	env = to_arr(*envps);
	execve(path, args, env);
	perror("command failed");
	exit(EXIT_FAILURE);
}

char	*find_path(char *file, char **arr)
{
	int		i;
	char	*path_buffer;

	// printf("cmd: %s\n", file);
	if (!arr || !*arr)
	{
		// TODO i'll make a function for it later
		if (access(file, X_OK | F_OK) == 0)
			return (ft_strdup(file));
		// TODO look at it at the end
		exit(EXIT_FAILURE);
	}
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
