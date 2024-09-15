/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:12:23 by yboumlak          #+#    #+#             */
/*   Updated: 2024/09/15 22:00:50 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

int	open_redirection_file(t_redirection *redir)
{
	int	flags;

	if (redir->type == TOKEN_REDIR_IN)
		flags = O_RDONLY;
	else if (redir->type == TOKEN_REDIR_OUT)
		flags = O_CREAT | O_TRUNC | O_WRONLY;
	else if (redir->type == TOKEN_REDIR_APPEND)
		flags = O_CREAT | O_APPEND | O_WRONLY;
	else if (redir->type == TOKEN_HEREDOC)
		flags = O_CREAT | O_APPEND | O_WRONLY;
	if (redir->file)
	{
		if (redir->fd != -1)
			close(redir->fd);
		redir->fd = open(redir->file, flags, 0644);
		if (redir->fd == -1)
		{
			perror("open");
			return (1);
		}
	}
	return (0);
}

t_redirection	*initialize_redirection(t_token **tokens)
{
	t_redirection	*redir;

	redir = malloc(sizeof(t_redirection));
	if (!redir)
		return (NULL);
	redir->type = (*tokens)->type;
	redir->next = NULL;
	redir->fd = -1;
	return (redir);
}

t_redirection	*initialize_file_token(t_token **tokens, t_redirection *redir,
		t_token **file_token)
{
	*file_token = (*tokens)->next;
	while (*file_token && (*file_token)->type == TOKEN_WHITESPACE)
		*file_token = (*file_token)->next;
	if (*file_token && ((*file_token)->type == TOKEN_WORD
			|| (*file_token)->type == TOKEN_ENV
			|| (*file_token)->type == TOKEN_SPECIAL_VAR))
	{
		redir->file = ft_strdup((*file_token)->value);
		*tokens = (*file_token)->next;
		return (redir);
	}
	return (NULL);
}

t_redirection	*parse_redirection(t_token **tokens)
{
	t_redirection	*redir;
	t_token			*file_token;
	t_redirection	*new_redir;

	file_token = NULL;
	redir = initialize_redirection(tokens);
	if (!redir)
		return (NULL);
	new_redir = initialize_file_token(tokens, redir, &file_token);
	if (!new_redir)
	{
		error("syntax error near unexpected token", "newline", 258);
		free(redir);
		return (NULL);
	}
	redir = new_redir;
	if (redir->type == TOKEN_HEREDOC)
		handle_heredoc(redir, file_token);
	else
		redir->delimiter = NULL;
	return (redir);
}

void	attach_redirections(t_tree_node *node, t_redirection *redir)
{
	t_redirection	*current;

	if (!node || !redir)
		return ;
	if (!node->redirections)
		node->redirections = redir;
	else
	{
		current = node->redirections;
		while (current->next)
			current = current->next;
		current->next = redir;
	}
}
