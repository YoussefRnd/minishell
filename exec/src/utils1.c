/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:23:31 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/09/15 15:52:46 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../parser/inc/parser.h"
#include "../inc/execution.h"

void	deal_with_open_files(t_redirection *node)
{
	while (node)
	{
		if (node->fd >= 0)
			close(node->fd);
		node = node->next;
	}
}

void	words_deal(t_tree_node *tree, t_env **env, bool *forked)
{
	pid_t	pid;

	signal(SIGINT, SIG_IGN);
	*forked = false;
	pid = fork();
	if (pid == 0)
	{
		signal_handler_in_c();
		cmd_execute(tree, env);
	}
	else if (pid == -1)
	{
		perror("fork failure");
		return ;
	}
	else
	{
		wait(&g_status);
		handle_exit_status();
		if (*forked)
			exit(g_status);
	}
}

void	subshells_deal(t_tree_node *tree, t_env **env, bool *forked)
{
	pid_t	pid;
	int		in;
	int		out;

	in = dup(STDIN_FILENO);
	out = dup(STDOUT_FILENO);
	handle_redirections_if_present(tree);
	*forked = true;
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (!pid)
	{
		_execute(tree->left, env, forked);
		exit(g_status);
	}
	else
	{
		wait(&g_status);
		handle_exit_status();
		handle_duplication_and_close(out, in);
	}
}

void	envs_deal(t_tree_node *tree, t_env **env, bool *forked)
{
	char	*value;

	value = get_value(*env, tree->token->value);
	if (value)
	{
		free(tree->token->value);
		tree->token->value = ft_strdup(value);
		tree->token->type = TOKEN_WORD;
		_execute(tree, env, forked);
	}
}

void	safe_free(char **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}
