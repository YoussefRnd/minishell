/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 10:37:11 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/09/10 15:28:26 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../inc/builtins.h"

void	handle_redirections_if_present(t_tree_node *tree)
{
	if (tree->redirections)
	{
		handle_redir(tree->redirections);
	}
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
	bool	flag;
	char	**args;

	in = dup(STDIN_FILENO);
	out = dup(STDOUT_FILENO);
	handle_redirections_if_present(tree);
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
	dup2(out, STDOUT_FILENO);
	dup2(in, STDIN_FILENO);
	close(out);
	close(in);
	return (0);
}

bool	flag_is_valid(char *str)
{
	char	*without_it;
	char	*without_n;

	without_it = ft_strtrim(str, "-");
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
