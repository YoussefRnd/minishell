/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 22:51:39 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/09/12 17:10:56 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/builtins.h"

int	is_valid_exit_argument(const char *str)
{
	if (str == NULL || *str == '\0')
	{
		return (0);
	}
	if (*str == '+' || *str == '-')
	{
		str++;
	}
	if (!ft_isdigit((unsigned char)*str))
	{
		return (0);
	}
	while (*str)
	{
		if (!ft_isdigit((unsigned char)*str))
		{
			return (0);
		}
		str++;
	}
	return (1);
}

void	print_exit_and_free_args(char **args)
{
	printf("exit\n");
	if (args)
		free_array(args);
}

void	handle_invalid_exit_argument(char **args)
{
	printf("exit: %s: numeric argument required\n", args[0]);
	free_array(args);
	exit(255);
}

void	handle_too_many_arguments(char **args)
{
	printf("exit: too many arguments\n");
	free_array(args);
}

int	respond_to_exit(t_tree_node *cmd_args, t_env **env)
{
	char	**args;
	int		exit_status;

	exit_status = 0;
	args = traverse_right_and_collect_values(cmd_args, env, false);
	print_exit_and_free_args(args);
	if (args && args[0])
	{
		if (!is_valid_exit_argument(args[0]))
			handle_invalid_exit_argument(args);
		if (args[1])
		{
			handle_too_many_arguments(args);
			return (1);
		}
		exit_status = ft_atoi(args[0]);
		free_array(args);
		exit(exit_status);
	}
	free_array(args);
	exit(status);
}
