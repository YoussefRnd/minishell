/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 22:51:39 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/08/06 21:53:07 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/builtins.h"

// int respond_to_exit(t_tree_node *cmd_args, t_env **env)
// {
//     char **args = traverse_right_and_collect_values(cmd_args, env, false);
//     if (args && args[1]){
//         printf("too many arguments\n");
//         return (-1);
//     }
//     if (args && args[0])
//         exit(ft_atoi(args[0]));
//     else
//         exit(exit_exit_status);
// }

// Function to check if a string is a valid integer argument for exit
int	is_valid_exit_argument(const char *str)
{
	// Empty string is not valid
	if (str == NULL || *str == '\0')
	{
		return (0);
	}
	// Check for leading + or - sign
	if (*str == '+' || *str == '-')
	{
		str++;
	}
	// At least one digit is required
	if (!ft_isdigit((unsigned char)*str))
	{
		return (0);
	}
	// Check the rest of the string for digits
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

int	respond_to_exit(t_tree_node *cmd_args, t_env **env)
{
	char	**args;

	args = traverse_right_and_collect_values(cmd_args, env, false);
	int exit_status = 0; // Default exit_status
	printf("exit\n");
	if (args)
	{
		// Handle the case with arguments
		if (args[0])
		{
			// If the first argument is not a valid integer
			if (!is_valid_exit_argument(args[0]))
			{
				printf("exit: %s: numeric argument required\n", args[0]);
				exit(2); // Exit exit_status for invalid numeric argument
			}
			// If there are more than one arguments
			if (args[1])
			{
				printf("exit: too many arguments\n");
				return (-1);
			}
			// If the first argument is valid
			exit_status = ft_atoi(args[0]);
		}
	}
	exit(status);
}
