/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:24:28 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/09/12 17:24:58 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../parser/inc/parser.h"
#include "../inc/execution.h"

void	left_side(t_tree_node *tree, t_env **env, bool *forked, int *pfd)
{
	close(pfd[0]);
	dup2(pfd[1], STDOUT_FILENO);
	close(pfd[1]);
	_execute(tree->left, env, forked);
	exit(EXIT_SUCCESS);
}

void	right_side(t_tree_node *tree, t_env **env, bool *forked, int *pfd)
{
	close(pfd[1]);
	dup2(pfd[0], STDIN_FILENO);
	close(pfd[0]);
	_execute(tree->right, env, forked);
	exit(status);
}

void	pipes_deal(t_tree_node *tree, t_env **env, bool *forked)
{
	int		pfd[2];
	int		substatus;
	pid_t	pidl;
	pid_t	pidr;

	pidl = 0;
	pidr = 0;
	ft_pipe(pfd);
	*forked = true;
	signal(SIGINT, SIG_IGN);
	pidl = fork();
	if (!pidl)
		left_side(tree, env, forked, pfd);
	if (pidl)
		pidr = fork();
	if (!pidr)
		right_side(tree, env, forked, pfd);
	close(pfd[0]);
	close(pfd[1]);
	waitpid(pidl, &substatus, 0);
	waitpid(pidr, &status, 0);
	handle_exit_status();
}

void	here_doc_deal(t_redirection *current)
{
	int	fd;

	fd = open(current->file, O_RDONLY);
	if (fd == -1)
	{
		perror("Herdoc");
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDIN_FILENO);
	unlink(current->file);
	close(fd);
}

void	handle_redir(t_redirection *current)
{
	while (current)
	{
		if (current->type == TOKEN_REDIR_OUT
			|| current->type == TOKEN_REDIR_APPEND)
		{
			open_redirection_file(current);
			if (current->fd == -1)
				exit(EXIT_FAILURE);
			dup2(current->fd, STDOUT_FILENO);
			close(current->fd);
		}
		else if (current->type == TOKEN_REDIR_IN)
		{
			open_redirection_file(current);
			if (current->fd == -1)
				exit(EXIT_FAILURE);
			dup2(current->fd, STDIN_FILENO);
			close(current->fd);
		}
		else if (current->type == TOKEN_HEREDOC)
		{
			here_doc_deal(current);
		}
		current = current->next;
	}
}
