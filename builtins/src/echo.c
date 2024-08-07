/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 10:37:11 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/08/07 01:54:49 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../inc/builtins.h"

// TODO check the bool that youssef is creating for the sake of spaces
int	respond_to_echo(t_tree_node *tree, t_env **env)
{
	bool	flag;
	int		i;
	char	**args;
	t_tree_node *current;
	int in = dup(STDIN_FILENO);
	int out = dup(STDOUT_FILENO);

	flag = false;
	i = 0;
	if (tree->redirections){
		handle_redir(tree->redirections);
	}
	args = traverse_right_and_collect_values(tree->right, env, false);
	if (!args)
		printf("\n");
	else
	{
		while (args[i] && (ft_strchr(args[i], '-') && ft_strchr(args[i], 'n')))
		{
			if (flag_is_valid(args[i]))
			{
				flag = true;
				i++;
			}
			else
				break ;
		}
		current = tree->right;
		while (args[i])
		{
			printf("%s", args[i]);
			i++;
			if (args[i] && !current->token->is_atached)
				printf(" ");
			current = current->right;
		}
		if (!flag)
			printf("\n");
	}
	dup2(out, STDOUT_FILENO);
	dup2(in, STDIN_FILENO);
	return (0);
}

bool	flag_is_valid(char *str)
{
	char *without_it = ft_strtrim(str, "-");
	char *without_n = ft_strtrim(without_it, "n");
	free(without_it);
	if (ft_strlen(without_n))
	{
		free(without_n);
		return (false);
	}
	else
	{
		free(without_n);
		return (true);
	}
}