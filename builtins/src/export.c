/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:55:29 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/09/13 01:03:25 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../inc/builtins.h"

void	print_list_exp(t_env *list)
{
	t_env	*current;

	current = list;
	while (current != NULL)
	{
		if (current->value == NULL)
		{
			printf("declare -x %s\n", current->key);
		}
		else
		{
			printf("declare -x %s=\"%s\"\n", current->key, current->value);
		}
		current = current->next;
	}
}

void	traverse_and_expand(t_tree_node *tree, t_env *env)
{
	t_tree_node	*current;
	char		*wraper;

	if (!tree || !env)
		return ;
	current = tree->right;
	while (current)
	{
		if (current->token->type == TOKEN_ENV)
		{
			wraper = ft_strdup(current->token->value);
			safe_free(&current->token->value);
			current->token->value = find_and_return_value(env, wraper);
			safe_free(&wraper);
			current->token->type = TOKEN_WORD;
		}
		current = current->right;
	}
}

void	free_n(t_tree_node **node)
{
	free_token(&(*node)->token);
	free_redirections(&(*node)->redirections);
	free(*node);
	*node = NULL;
}

void	remove_node(t_tree_node **head, t_tree_node *node_to_remove)
{
	t_tree_node	*prev;
	t_tree_node	*temp;

	if (*head == NULL || node_to_remove == NULL)
		return ;
	if (*head == node_to_remove)
		*head = node_to_remove->right;
	prev = NULL;
	temp = *head;
	while (temp != NULL && temp != node_to_remove)
	{
		prev = temp;
		temp = temp->right;
	}
	if (temp == NULL)
		return ;
	if (prev != NULL)
		prev->right = node_to_remove->right;
	free_n(&node_to_remove);
}

void	update_current_token_value(t_tree_node *current, char **copy)
{
	*copy = ft_strdup(current->token->value);
	safe_free(&current->token->value);
	current->token->value = ft_strjoin(*copy, current->right->token->value);
	safe_free(copy);
}
