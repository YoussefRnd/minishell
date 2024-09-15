/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 12:39:40 by yboumlak          #+#    #+#             */
/*   Updated: 2024/09/15 20:19:20 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lexer.h"

// t_token	*process_quote_end(char **input, char *start, t_quote *state,
// 		t_token *temp_token)
// {
// 	char	*value;

// 	value = ft_strndup(start, *input - start);
// 	(*input)++;
// 	if (ft_strlen(value) == 0)
// 		return (create_token(TOKEN_EMPTY, value, *state));
// 	if (temp_token != NULL && temp_token->type != TOKEN_EMPTY)
// 		return (temp_token);
// 	return (create_token(TOKEN_WORD, value, *state));
// }

// t_token	*handle_dollar_in_quotes(char **input, t_quote *state,
// 		t_token **last_token, t_token **temp_token)
// {
// 	if (*last_token != NULL)
// 	{
// 		(*last_token)->next = handle_dollar(input, *state);
// 		*last_token = (*last_token)->next;
// 	}
// 	else
// 	{
// 		*temp_token = handle_dollar(input, *state);
// 		*last_token = *temp_token;
// 	}
// 	return (*temp_token);
// }

// t_token	*handle_non_dollar_in_quotes(char **input, t_quote *state,
// 		t_token **last_token, t_token **temp_token)
// {
// 	if (*last_token != NULL)
// 	{
// 		(*last_token)->next = handle_non_alnum(input, *state);
// 		*last_token = (*last_token)->next;
// 	}
// 	else
// 	{
// 		*temp_token = handle_non_alnum(input, *state);
// 		*last_token = *temp_token;
// 	}
// 	return (*temp_token);
// }

// t_token	*handle_quote_content(char **input, t_quote *state, char quote_type)
// {
// 	char	*start;
// 	t_token	*temp_token;
// 	t_token	*last_token;

// 	last_token = NULL;
// 	start = *input;
// 	temp_token = NULL;
// 	while (**input != '\0')
// 	{
// 		if (**input == '$' && *state == IN_DQUOTES)
// 			temp_token = handle_dollar_in_quotes(input, state, &last_token,
// 					&temp_token);
// 		else if (**input == quote_type)
// 			return (process_quote_end(input, start, state, temp_token));
// 		else
// 			temp_token = handle_non_dollar_in_quotes(input, state, &last_token,
// 					&temp_token);
// 		if ((**input != '$' || *state != IN_DQUOTES) && **input != '\'')
// 			(*input)++;
// 	}
// 	return (temp_token);
// }

// t_token	*handle_quote(char **input, t_quote *state)
// {
// 	char	quote_type;
// 	t_token	*temp_token;

// 	quote_type = **input;
// 	if (**input == '\"')
// 		*state = IN_DQUOTES;
// 	else
// 		*state = IN_QUOTES;
// 	(*input)++;
// 	temp_token = handle_quote_content(input, state, quote_type);
// 	if (temp_token)
// 		return (temp_token);
// 	error("Syntax error: unmatched quote", NULL, 1);
// 	return (create_token(TOKEN_ERROR, ft_strdup(""), *state));
// }


// t_token	*handle_quote(char **input, t_quote *state)
// {
// 	t_token	*temp_token;
// 	t_token	*last_token;
// 	t_token	*head_token = NULL;
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
// 	last_token = NULL;
// 	while (**input != '\0')
// 	{
// 		if (**input == '$' && *state == IN_DQUOTES)
// 		{
// 			if (start != *input)
//             {
//                 value = ft_strndup(start, *input - start);
//                 temp_token = create_token(TOKEN_WORD, value, *state);
//                 if (last_token != NULL)
//                     last_token->next = temp_token;
//                 else
//                     head_token = temp_token;
//                 last_token = temp_token;
//             }
// 			temp_token = handle_dollar(input, *state);
// 			if (!temp_token)
// 				continue;
// 			if (last_token != NULL)
// 				last_token->next = temp_token;
// 			else
// 				head_token = temp_token;
// 			last_token = temp_token;
// 			start = *input;
// 		}
// 		if (**input == quote_type)
// 		{
// 			value = ft_strndup(start, *input - start);
// 			if (ft_strlen(value) == 0)
// 				temp_token = create_token(TOKEN_EMPTY, value, *state);
// 			else
// 				temp_token = create_token(TOKEN_WORD, value, *state);
// 			if (last_token != NULL)
// 				last_token->next = temp_token;
// 			else
// 				head_token = temp_token;
// 			last_token = temp_token;
// 			(*input)++;
// 			return head_token;
// 		}
// 		if (**input != '$' || *state != IN_DQUOTES)
// 			(*input)++;
// 	}
// 	error("Syntax error: unmatched quote", NULL, 1);
// 	return (create_token(TOKEN_ERROR, ft_strdup(""), *state));
// }

typedef struct s_quote_state
{
	t_token	*head_token;
	t_token	*last_token;
	char	*start;
}	t_quote_state;


void	link_tokens(t_quote_state *qstate, t_token *new_token)
{
	if (qstate->last_token != NULL)
		qstate->last_token->next = new_token;
	else
		qstate->head_token = new_token;
	qstate->last_token = new_token;
}


t_token	*process_quote_end(char **input, t_quote *state, t_quote_state *qstate, char **start)
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
			continue;
		if (**input == quote_type)
			return (process_quote_end(input, state, &qstate, input));
		(*input)++;
	}
	error("Syntax error: unmatched quote", NULL, 1);
	return (create_token(TOKEN_ERROR, ft_strdup(""), *state));
}
