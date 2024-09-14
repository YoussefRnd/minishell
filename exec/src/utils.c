/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 09:43:36 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/09/14 15:54:17 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../parser/inc/parser.h"
#include "../inc/execution.h"

char	*find_and_return_value(t_env *head_ref, char *key)
{
	t_env	*current;

	current = head_ref;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (ft_strdup(current->value));
		current = current->next;
	}
	return (NULL);
}

char	*get_value(t_env *env, char *key)
{
	t_env	*current;

	current = env;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			return (current->value);
		}
		current = current->next;
	}
	return (NULL);
}

char	**allocate_array(t_tree_node *head, char *path)
{
	int		count;
	char	**array;

	count = count_nodes(head);
	array = (char **)malloc((count + 2) * sizeof(char *));
	if (array != NULL)
	{
		array[0] = ft_strdup(path);
	}
	return (array);
}

void	process_tok(t_tree_node *current, t_env *env)
{
	char	*value;

	if (current->token->type == TOKEN_ENV)
	{
		value = get_value(env, current->token->value);
		free(current->token->value);
		if (value)
			current->token->value = ft_strdup(value);
		else
			current->token->value = ft_strdup("");
	}
}

void	pipes_deal(t_tree_node *tree, t_env **env, bool *forked)
{
	int		pfd[2];
	int		substatus;
	pid_t	pidl;
	pid_t	pidr;

	pidl = 0;
	pidr = 0;
	ft_pipe(pfd);
	*forked = true;
	signal(SIGINT, SIG_IGN);
	pidl = fork();
	if (!pidl)
		left_side(tree, env, forked, pfd);
	if (pidl)
		pidr = fork();
	if (!pidr)
		right_side(tree, env, forked, pfd);
	close(pfd[0]);
	close(pfd[1]);
	waitpid(pidl, &substatus, 0);
	waitpid(pidr, &g_status, 0);
	handle_exit_status();
}
