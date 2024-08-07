/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 11:37:25 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/08/07 13:30:37 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../inc/builtins.h"

int	respond_to_pwd(t_tree_node *cmd)
{
	int in = dup(STDIN_FILENO);
	int out = dup(STDOUT_FILENO);
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		if (cmd->redirections)
			handle_redir(cmd->redirections);
		printf("%s\n", cwd);
		dup2(out, STDOUT_FILENO);
		dup2(in, STDIN_FILENO);
		return (0);
	}
	else
		perror("getcwd() error");
	return (1);
}
