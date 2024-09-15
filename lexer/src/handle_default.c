/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_default.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:24:33 by yboumlak          #+#    #+#             */
/*   Updated: 2024/09/15 21:25:09 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lexer.h"

t_token	*create_token(t_token_type type, char *value, t_quote state)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->type = type;
	token->value = value;
	token->state = state;
	token->subtokens = NULL;
	token->next = NULL;
	token->is_atached = false;
	return (token);
}

t_token	*handle_whitespace(char **input, t_quote state)
{
	char	*start;
	char	*value;

	start = *input;
	while (ft_isspace(**input))
		(*input)++;
	value = ft_strndup(start, *input - start);
	return (create_token(TOKEN_WHITESPACE, value, state));
}

t_token_type	is_builtin(char *value)
{
	if (!ft_strcmp(value, "echo"))
		return (TOKEN_BUILTIN);
	else if (!ft_strcmp(value, "cd"))
		return (TOKEN_BUILTIN);
	else if (!ft_strcmp(value, "pwd"))
		return (TOKEN_BUILTIN);
	else if (!ft_strcmp(value, "export"))
		return (TOKEN_BUILTIN);
	else if (!ft_strcmp(value, "unset"))
		return (TOKEN_BUILTIN);
	else if (!ft_strcmp(value, "env"))
		return (TOKEN_BUILTIN);
	else if (!ft_strcmp(value, "exit"))
		return (TOKEN_BUILTIN);
	else
		return (TOKEN_WORD);
}

t_token	*handle_env_digit(char **input, t_quote state)
{
	char	*start;
	char	*value;

	start = *input;
	(*input)++;
	while (ft_isdigit(**input))
		(*input)++;
	value = ft_strndup(start, *input - start);
	return (create_token(TOKEN_WORD, value, state));
}

t_token	*handle_default(char **input, t_quote state)
{
	char	*start;
	char	*value;

	start = *input;
	while (!ft_isspace(**input) && !strchr("<>|&$\"\'", **input))
		(*input)++;
	value = ft_strndup(start, *input - start);
	if (ft_strchr(value, '*'))
		return (create_token(TOKEN_WILDCARD, value, state));
	return (create_token(is_builtin(value), value, state));
}
