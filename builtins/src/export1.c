/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:12:26 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/09/13 01:12:13 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../inc/builtins.h"

void	set_attached_and_remove_node(t_tree_node **tree, t_tree_node *current,
		bool smtg)
{
	current->token->is_atached = smtg;
	remove_node(tree, current->right);
}

void	prep_it(t_tree_node *tree)
{
	t_tree_node	*current;
	char		*copy;

	current = tree->right;
	while (current)
	{
		while (current->token->is_atached)
		{
			if (current->right)
			{
				update_current_token_value(current, &copy);
				if (current->right->token->is_atached)
					set_attached_and_remove_node(&tree, current, true);
				else
					set_attached_and_remove_node(&tree, current, false);
			}
			else
				break ;
		}
		current = current->right;
	}
}

bool	check_validity(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return (false);
	while (args[i])
	{
		if (ft_strlen(args[i]) > 0)
			return (true);
		i++;
	}
	return (false);
}

int	respond_to_export(t_env **list, t_tree_node *cmd)
{
	int		in;
	int		out;
	int		i;
	char	**args;

	i = -1;
	in = dup(STDIN_FILENO);
	out = dup(STDOUT_FILENO);
	traverse_and_expand(cmd, *list);
	prep_it(cmd);
	args = traverse_right_and_collect_values(cmd->right, list, false);
	if (cmd->redirections)
		handle_redir(cmd->redirections);
	if (!check_validity(args))
		print_list_exp(*list);
	else
		while (args[++i])
			append_node(list, args[i]);
	free_array(args);
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	close(out);
	close(in);
	return (0);
}
