/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 12:42:43 by yboumlak          #+#    #+#             */
/*   Updated: 2024/09/15 21:56:13 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lexer.h"

t_token	*create_env_token(char **input, t_quote state)
{
	char	*start;
	char	*value;

	if ((ft_isalpha(**input) || **input == '_'))
	{
		start = *input;
		while (ft_isalnum(**input) || **input == '_')
			(*input)++;
		value = ft_strndup(start, *input - start);
		return (create_token(TOKEN_ENV, value, state));
	}
	return (create_token(TOKEN_EMPTY, ft_strdup(""), state));
}

t_token	*handle_double_dollar(char **input, t_quote state)
{
	int		count;
	char	*start;
	char	*value;

	count = 0;
	while (**input == '$')
	{
		count++;
		(*input)++;
	}
	if (count % 2 == 0)
	{
		start = *input;
		while (**input && !isspace(**input) && **input != '$'
			&& **input != '\"')
			(*input)++;
		value = ft_strndup(start, *input - start);
		return (create_token(TOKEN_WORD, value, state));
	}
	else
		return (create_env_token(input, state));
}

t_token	*handle_env_var(char **input, t_quote state)
{
	char	*start;
	char	*value;

	start = *input;
	while (ft_isalnum(**input) || **input == '_')
		(*input)++;
	value = ft_strndup(start, *input - start);
	if (ft_strlen(value) == 0)
		return (NULL);
	if (state == NORMAL || state == IN_DQUOTES)
		return (create_token(TOKEN_ENV, value, state));
	return (create_token(TOKEN_WORD, value, state));
}

t_token	*handle_non_alnum(char **input, t_quote state)
{
	char	*start;
	char	*value;

	(*input)--;
	start = *input;
	while (!ft_isspace(**input) && !strchr("<>|&\"\'", **input))
		(*input)++;
	value = ft_strndup(start, *input - start);
	return (create_token(TOKEN_WORD, value, state));
}

t_token	*handle_dollar(char **input, t_quote state)
{
	(*input)++;
	if (**input == '?')
	{
		(*input)++;
		return (create_token(TOKEN_SPECIAL_VAR, ft_strdup("?"), state));
	}
	if (**input == '$')
	{
		(*input)--;
		return (handle_double_dollar(input, state));
	}
	if (ft_isdigit(**input))
	{
		(*input)--;
		return (handle_env_digit(input, state));
	}
	if ((ft_isalpha(**input) || **input == '_') && **input != '\0')
		return (handle_env_var(input, state));
	return (handle_non_alnum(input, state));
}
