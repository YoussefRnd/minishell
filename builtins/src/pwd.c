/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 11:37:25 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/09/14 15:11:23 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../inc/builtins.h"

int	respond_to_pwd(t_tree_node *cmd)
{
	int		in;
	int		i;
	int		out;
	char	cwd[1024];

	in = dup(STDIN_FILENO);
	out = dup(STDOUT_FILENO);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		if (cmd->redirections)
		{
			i = handle_redir(cmd->redirections);
			if (i)
				return (1);
		}
		printf("%s\n", cwd);
		dup2(out, STDOUT_FILENO);
		dup2(in, STDIN_FILENO);
		close(out);
		close(in);
		return (0);
	}
	else
		perror("getcwd() error");
	return (1);
}
