/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 19:26:27 by yboumlak          #+#    #+#             */
/*   Updated: 2024/09/14 15:11:28 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

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

void	handle_heredoc(t_redirection *redir, t_token *file_token)
{
	printf("token type: %d\n", file_token->type);
	if (file_token->type == TOKEN_ENV)
	{
		redir->delimiter = ft_strjoin("$", redir->file);
		free(redir->file);
	}
	else
		redir->delimiter = redir->file;
	redir->file = "/tmp/heredoc";
	open_redirection_file(redir);
	here_doc(redir);
	close(redir->fd);
}
