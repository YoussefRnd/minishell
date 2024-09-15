/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 10:37:11 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/09/14 15:40:39 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../inc/builtins.h"

int	handle_redirections_if_present(t_tree_node *tree)
{
	int	i;

	i = 0;
	if (tree->redirections)
		i = handle_redir(tree->redirections);
	if (i)
		return (1);
	return (0);
}

void	print_args(char **args, t_tree_node *tree)
{
	int			i;
	t_tree_node	*current;
	bool		printable;

	i = 0;
	printable = false;
	current = tree->right;
	while (args[i])
	{
		if (!printable && flag_is_valid(args[i]))
		{
			i++;
			current = current->right;
			continue ;
		}
		printable = true;
		printf("%s", args[i]);
		i++;
		if (args[i] && !current->token->is_atached)
			printf(" ");
		current = current->right;
	}
}

bool	process_flags(char **args)
{
	bool	flag;
	int		i;

	flag = false;
	i = 0;
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
	return (flag);
}

int	respond_to_echo(t_tree_node *tree, t_env **env)
{
	int		in;
	int		out;
	int		i;
	bool	flag;
	char	**args;

	in = dup(STDIN_FILENO);
	out = dup(STDOUT_FILENO);
	i = handle_redirections_if_present(tree);
	if (i)
		return (1);
	args = traverse_right_and_collect_values(tree->right, env, false);
	if (!args)
		printf("\n");
	else
	{
		flag = process_flags(args);
		print_args(args, tree);
		if (!flag)
			printf("\n");
	}
	free_array(args);
	handle_duplication_and_close(out, in);
	return (0);
}

bool	flag_is_valid(char *str)
{
	char	*without_it;
	char	*without_n;

	without_it = ft_strtrim(str, "-");
	if (ft_strlen(without_it) == 0)
	{
		free(without_it);
		return (false);
	}
	without_n = ft_strtrim(without_it, "n");
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
