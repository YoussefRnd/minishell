/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:14:12 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/09/10 12:43:06 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../parser/inc/parser.h"
#include "../inc/builtins.h"

int	respond_to_b(t_tree_node *cmd, t_env **env)
{
	if (ft_strcmp(cmd->token->value, "cd") == 0)
		return (respond_to_cd(cmd->right, env));
	else if (ft_strcmp(cmd->token->value, "env") == 0)
		return (respond_to_env(*env, cmd));
	else if (ft_strcmp(cmd->token->value, "export") == 0)
		return (respond_to_export(env, cmd));
	else if (ft_strcmp(cmd->token->value, "unset") == 0)
		return (respond_to_unset(env, cmd));
	else if (ft_strcmp(cmd->token->value, "exit") == 0)
		return (respond_to_exit(cmd->right, env));
	else if (ft_strcmp(cmd->token->value, "pwd") == 0)
		return (respond_to_pwd(cmd));
	else if (ft_strcmp(cmd->token->value, "echo") == 0)
		return (respond_to_echo(cmd, env));
	return (0);
}
