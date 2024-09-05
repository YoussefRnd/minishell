/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 12:39:40 by yboumlak          #+#    #+#             */
/*   Updated: 2024/09/05 13:27:36 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lexer.h"

// t_token	*handle_quote(char **input, t_quote *state)
// {
// 	t_token	*temp_token;
// 	char	quote_type;
// 	char	*start;
// 	char	*value;

// 	quote_type = **input;
// 	if (**input == '\"')
// 		*state = IN_DQUOTES;
// 	else
// 		*state = IN_QUOTES;
// 	(*input)++;
// 	start = *input;
// 	temp_token = NULL;
// 	while (**input != '\0')
// 	{
// 		if (**input == '$' && *state == IN_DQUOTES)
// 			temp_token = handle_dollar(input, *state);
// 		if (**input == quote_type)
// 		{
// 			value = ft_strndup(start, *input - start);
// 			(*input)++;
// 			if (ft_strlen(value) == 0)
// 				return (create_token(TOKEN_EMPTY, value, *state));
// 			if (temp_token != NULL)
// 				return (temp_token);
// 			else
// 				return (create_token(TOKEN_WORD, value, *state));
// 		}
// 		(*input)++;
// 	}
// 	error("Syntax error: unmatched quote", NULL, 1);
// 	return (create_token(TOKEN_ERROR, ft_strdup(""), *state));
// }

t_token	*process_quote_end(char **input, char *start, t_quote *state,
		t_token *temp_token)
{
	char	*value;

	value = ft_strndup(start, *input - start);
	(*input)++;
	if (ft_strlen(value) == 0)
		return (create_token(TOKEN_EMPTY, value, *state));
	if (temp_token != NULL)
		return (temp_token);
	return (create_token(TOKEN_WORD, value, *state));
}

t_token	*handle_quote_content(char **input, t_quote *state, char quote_type)
{
	char	*start;
	t_token	*temp_token;

	start = *input;
	temp_token = NULL;
	while (**input != '\0')
	{
		if (**input == '$' && *state == IN_DQUOTES)
			temp_token = handle_dollar(input, *state);
		if (**input == quote_type)
			return (process_quote_end(input, start, state, temp_token));
		(*input)++;
	}
	return (NULL);
}

t_token	*handle_quote(char **input, t_quote *state)
{
	char	quote_type;
	t_token	*temp_token;

	quote_type = **input;
	if (**input == '\"')
		*state = IN_DQUOTES;
	else
		*state = IN_QUOTES;
	(*input)++;
	temp_token = handle_quote_content(input, state, quote_type);
	if (temp_token)
		return (temp_token);
	error("Syntax error: unmatched quote", NULL, 1);
	return (create_token(TOKEN_ERROR, ft_strdup(""), *state));
}
