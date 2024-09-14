/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:24:28 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/09/14 15:54:17 by hbrahimi         ###   ########.fr       */
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
	exit(g_status);
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

int	handle_redirection_and_return_status(t_redirection *current, int fd)
{
	int	i;

	i = open_redirection_file(current);
	if (i)
		return (1);
	dup2(current->fd, fd);
	close(current->fd);
	return (0);
}

int	handle_redir(t_redirection *current)
{
	int	i;

	while (current)
	{
		if (current->type == TOKEN_REDIR_OUT
			|| current->type == TOKEN_REDIR_APPEND)
		{
			i = handle_redirection_and_return_status(current, STDOUT_FILENO);
			if (i)
				return (1);
		}
		else if (current->type == TOKEN_REDIR_IN)
		{
			i = handle_redirection_and_return_status(current, STDIN_FILENO);
			if (i)
				return (1);
		}
		else if (current->type == TOKEN_HEREDOC)
			here_doc_deal(current);
		current = current->next;
	}
	return (0);
}
