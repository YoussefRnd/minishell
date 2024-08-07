/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 09:49:31 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/08/07 13:10:56 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../inc/builtins.h"

t_env	*create_env_dict(char **env)
{
	t_env	*head;

	if (!env)
		return (NULL);
	head = NULL;
	while (*env)
	{
		append_node(&head, *env);
		env++;
	}
	return (head);
}

int	respond_to_env(t_env *the_whole_list, t_tree_node *cmd)
{
	int in = dup(STDIN_FILENO);
	int out = dup(STDOUT_FILENO);
	if (cmd->redirections)
		handle_redir(cmd->redirections);
	print_list(the_whole_list);
	dup2(out, STDOUT_FILENO);
	dup2(in, STDIN_FILENO);
	return (1);
	// TODO this to be handled in case of a variable that doesn't conatain a va
	// lue example exort this=
}

