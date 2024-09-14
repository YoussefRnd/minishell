/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 23:27:18 by yboumlak          #+#    #+#             */
/*   Updated: 2024/09/04 23:27:23 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lexer.h"

t_token	*handle_redirection(char **input, char redir, t_quote state)
{
	char	*start;
	char	*value;

	start = *input;
	while (**input == redir)
		(*input)++;
	value = ft_strndup(start, *input - start);
	if (redir == '<')
	{
		if (ft_strlen(value) == 1)
			return (create_token(TOKEN_REDIR_IN, value, state));
		else if (ft_strlen(value) == 2)
			return (create_token(TOKEN_HEREDOC, value, state));
	}
	else if (redir == '>')
	{
		if (ft_strlen(value) == 1)
			return (create_token(TOKEN_REDIR_OUT, value, state));
		else if (ft_strlen(value) == 2)
			return (create_token(TOKEN_REDIR_APPEND, value, state));
	}
	error("minishell: syntax error near unexpected token", value, 258);
	return (create_token(TOKEN_ERROR, ft_strdup(""), state));
}
