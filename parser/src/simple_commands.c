/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:52:33 by yboumlak          #+#    #+#             */
/*   Updated: 2024/09/13 23:40:19 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

t_tree_node	*add_subshell_token_to_tree(t_token **tokens, t_tree_node **node,
		t_tree_node **current)
{
	t_tree_node	*subshell_node;

	subshell_node = parse_subshell(tokens);
	if (*node == NULL)
	{
		*node = subshell_node;
		*current = *node;
	}
	else
	{
		(*current)->right = subshell_node;
		*current = (*current)->right;
	}
	return (*node);
}

bool	add_redirection_token_to_node(t_token **tokens,
		t_redirection **redirections, t_tree_node **node)
{
	t_redirection	*new_redir;
	t_redirection	*last_redir;

	new_redir = parse_redirection(tokens);
	if (new_redir == NULL)
	{
		free_tree(node);
		return (false);
	}
	if (*redirections == NULL)
		*redirections = new_redir;
	else
	{
		last_redir = *redirections;
		while (last_redir->next)
			last_redir = last_redir->next;
		last_redir->next = new_redir;
	}
	return (true);
}

void	create_tree_node_from_token(t_token **tokens, t_tree_node **node,
		t_tree_node **current, t_redirection **redirections)
{
	if (*node == NULL)
	{
		*node = create_tree_node(*tokens);
		*current = *node;
		if (*redirections)
		{
			attach_redirections(*node, *redirections);
			*redirections = NULL;
		}
	}
	else
	{
		(*current)->right = create_tree_node(*tokens);
		*current = (*current)->right;
	}
}

void	process_tokens(t_token **tokens, t_tree_node **node,
		t_tree_node **current, t_redirection **redirections)
{
	if (is_env_token_attached(tokens))
		(*tokens)->is_atached = true;
	if ((*tokens)->type == TOKEN_WHITESPACE || (*tokens)->type == TOKEN_EMPTY)
	{
		*tokens = (*tokens)->next;
		return ;
	}
	if ((*tokens)->type == TOKEN_SUBSHELL)
	{
		*node = add_subshell_token_to_tree(tokens, node, current);
		return ;
	}
	if (is_redirection_token(tokens))
	{
		if (!add_redirection_token_to_node(tokens, redirections, node))
			*tokens = (*tokens)->next;
		return ;
	}
	concatenate_tokens_if_needed(tokens);
	if ((*tokens)->type == TOKEN_WILDCARD && add_wildcard_token_to_tree(tokens,
			node, current))
		return ;
	create_tree_node_from_token(tokens, node, current, redirections);
	*tokens = (*tokens)->next;
}

t_tree_node	*parse_command(t_token **tokens)
{
	t_tree_node		*node;
	t_tree_node		*current;
	t_redirection	*redirections;

	node = NULL;
	current = NULL;
	redirections = NULL;
	while (*tokens && is_valid_token((*tokens)->type))
		process_tokens(tokens, &node, &current, &redirections);
	if (node && redirections)
		attach_redirections(node, redirections);
	else if (!node && redirections)
		free_redirections(&redirections);
	return (node);
}
