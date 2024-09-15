/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe_and_or.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 23:23:21 by yboumlak          #+#    #+#             */
/*   Updated: 2024/09/05 13:26:08 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lexer.h"

t_token	*handle_ampersand(char **input, t_quote state)
{
	char	*start;
	char	*value;

	start = *input;
	while (**input == '&')
		(*input)++;
	value = ft_strndup(start, *input - start);
	if (ft_strlen(value) == 1)
		return (create_token(TOKEN_WORD, value, state));
	else if (ft_strlen(value) == 2)
		return (create_token(TOKEN_AND, value, state));
	error("minishell: syntax error near unexpected token", value, 258);
	return (create_token(TOKEN_ERROR, ft_strdup(""), state));
}

t_token	*handle_pipe(char **input, t_quote state)
{
	char	*start;
	char	*value;

	start = *input;
	while (**input == '|')
		(*input)++;
	value = ft_strndup(start, *input - start);
	if (ft_strlen(value) == 1)
		return (create_token(TOKEN_PIPE, value, state));
	else if (ft_strlen(value) == 2)
		return (create_token(TOKEN_OR, value, state));
	else
	{
		error("minishell: syntax error near unexpected token", value, 258);
		return (create_token(TOKEN_ERROR, ft_strdup(""), state));
	}
}
