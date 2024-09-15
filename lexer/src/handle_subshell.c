/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_subshell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 21:35:13 by yboumlak          #+#    #+#             */
/*   Updated: 2024/09/04 21:35:19 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lexer.h"

int	find_subshell_end(char **input, int *nesting_level)
{
	while (**input && *nesting_level > 0)
	{
		if (**input == '(')
			(*nesting_level)++;
		else if (**input == ')')
			(*nesting_level)--;
		(*input)++;
	}
	if (*nesting_level != 0)
	{
		error("minishell: syntax error near unexpected token", *input, 1);
		return (0);
	}
	return (1);
}

char	*extract_subshell_value(char *start, int length)
{
	char	*value;

	value = ft_strndup(start, length);
	if (!value)
		return (NULL);
	return (value);
}

t_token	*create_subshell_token(char *value, t_quote state)
{
	t_token	*subshell_token;

	subshell_token = create_token(TOKEN_SUBSHELL, value, state);
	if (!subshell_token)
		return (NULL);
	return (subshell_token);
}

t_token	*tokenize_subshell(char **subshell_input, t_token *subshell_token)
{
	t_token	*token;
	t_token	*last_token;

	last_token = NULL;
	while (1)
	{
		token = get_next_token(subshell_input);
		if (!last_token)
			subshell_token->subtokens = token;
		else
			last_token->next = token;
		last_token = token;
		if (token->type == TOKEN_EOF)
			break ;
	}
	return (last_token);
}

t_token	*handle_subshell(char **input, t_quote state)
{
	char	*start;
	int		nesting_level;
	char	*value;
	t_token	*subshell_token;
	t_token	*last_token;

	(*input)++;
	start = *input;
	nesting_level = 1;
	if (!find_subshell_end(input, &nesting_level))
		return (create_token(TOKEN_ERROR, ft_strdup(""), state));
	value = extract_subshell_value(start, *input - start - 1);
	if (!value || ft_strlen(value) == 0)
	{
		error("minishell: syntax error near unexpected token", ")", 258);
		free(value);
		return (create_token(TOKEN_ERROR, ft_strdup(""), state));
	}
	subshell_token = create_subshell_token(value, state);
	last_token = tokenize_subshell(&value, subshell_token);
	return (subshell_token);
}
