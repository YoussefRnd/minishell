/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 12:39:40 by yboumlak          #+#    #+#             */
/*   Updated: 2024/09/15 21:32:22 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lexer.h"

void	link_tokens(t_quote_state *qstate, t_token *new_token)
{
	if (qstate->last_token != NULL)
		qstate->last_token->next = new_token;
	else
		qstate->head_token = new_token;
	qstate->last_token = new_token;
}

t_token	*process_quote_end(char **input, t_quote *state, t_quote_state *qstate)
{
	t_token	*temp_token;
	char	*value;

	value = ft_strndup(qstate->start, *input - qstate->start);
	if (ft_strlen(value) == 0)
		temp_token = create_token(TOKEN_EMPTY, value, *state);
	else
		temp_token = create_token(TOKEN_WORD, value, *state);
	link_tokens(qstate, temp_token);
	(*input)++;
	return (qstate->head_token);
}

int	process_dollar_in_quote(char **input, t_quote *state, t_quote_state *qstate)
{
	t_token	*temp_token;
	char	*value;

	if (**input == '$' && *state == IN_DQUOTES)
	{
		if (qstate->start != *input)
		{
			value = ft_strndup(qstate->start, *input - qstate->start);
			temp_token = create_token(TOKEN_WORD, value, *state);
			link_tokens(qstate, temp_token);
		}
		temp_token = handle_dollar(input, *state);
		if (temp_token)
			link_tokens(qstate, temp_token);
		qstate->start = *input;
		return (1);
	}
	return (0);
}

t_token	*handle_quote(char **input, t_quote *state)
{
	char			quote_type;
	t_quote_state	qstate;

	quote_type = **input;
	if (**input == '\"')
		*state = IN_DQUOTES;
	else
		*state = IN_QUOTES;
	(*input)++;
	qstate.start = *input;
	qstate.head_token = NULL;
	qstate.last_token = NULL;
	while (**input != '\0')
	{
		if (process_dollar_in_quote(input, state, &qstate))
			continue ;
		if (**input == quote_type)
			return (process_quote_end(input, state, &qstate));
		(*input)++;
	}
	error("Syntax error: unmatched quote", NULL, 1);
	return (create_token(TOKEN_ERROR, ft_strdup(""), *state));
}
