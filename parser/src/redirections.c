/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:12:23 by yboumlak          #+#    #+#             */
/*   Updated: 2024/07/29 14:14:44 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	open_redirection_file(t_redirection *redir)
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
			perror("open");
	}
}

void	here_doc(t_redirection *redir)
{
	char	*line;
	char	*tmp;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, redir->delimiter) == 0)
		{
			free(line);
			break ;
		}
		tmp = ft_strjoin(line, "\n");
		write(redir->fd, tmp, ft_strlen(tmp));
		free(tmp);
		free(line);
	}
}

t_redirection	*parse_redirection(t_token **tokens)
{
	t_redirection	*redir;
	t_token			*file_token;

	redir = malloc(sizeof(t_redirection));
	if (!redir)
		return (NULL);
	redir->type = (*tokens)->type;
	redir->next = NULL;
	redir->fd = -1;
	file_token = (*tokens)->next;
	while (file_token && file_token->type == TOKEN_WHITESPACE)
		file_token = file_token->next;
	if (file_token && file_token->type == TOKEN_WORD)
	{
		redir->file = strdup(file_token->value);
		*tokens = file_token->next;
	}
	else
	{
		redir->file = NULL;
		*tokens = (*tokens)->next;
	}
	if (redir->type == TOKEN_HEREDOC)
	{
		redir->delimiter = redir->file;
		redir->file = "/tmp/heredoc";
		open_redirection_file(redir);
		here_doc(redir);
	}
	else
	{
		redir->delimiter = NULL;
		open_redirection_file(redir);
	}
	return (redir);
}

void	attach_redirections(t_tree_node *node, t_redirection *redir)
{
	t_redirection	*current;

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
