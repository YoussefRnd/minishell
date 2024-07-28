/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 11:10:43 by yboumlak          #+#    #+#             */
/*   Updated: 2024/07/28 15:59:04 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lexer.h"

void	error(char *msg, char *token)
{
	printf("%s `%s'\n", msg, token);
}

t_token	*create_token(t_token_type type, char *value, t_quote state)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->type = type;
	token->value = value;
	token->state = state;
	token->subtokens = NULL;
	token->next = NULL;
	return (token);
}

t_token	*get_next_token(char **input)
{
	char	*start;
	char	*value;
	int		nesting_level;
	char	*subshell_input;
	t_token	*subshell_token;
	t_token	*last_token;
	t_token	*token;
	t_quote	state;
	char	quote_type;

	state = NORMAL;
	value = NULL;
	if (**input == '\0')
		return (create_token(TOKEN_EOF, "", state));
	if (isspace(**input))
	{
		start = *input;
		while (isspace(**input))
			(*input)++;
		value = strndup(start, *input - start);
		return (create_token(TOKEN_WHITESPACE, value, state));
	}
	else if (**input == '|')
	{
		start = *input;
		while (**input == '|')
			(*input)++;
		value = strndup(start, *input - start);
		if (ft_strlen(value) == 1)
			return (create_token(TOKEN_PIPE, "|", state));
		else if (ft_strlen(value) == 2)
			return (create_token(TOKEN_OR, value, state));
		else
		{
			error("minishell: syntax error near unexpected token", value);
			return (create_token(TOKEN_ERROR, "", state));
		}
	}
	else if (**input == '<')
	{
		start = *input;
		while (**input == '<')
			(*input)++;
		value = strndup(start, *input - start);
		if (ft_strlen(value) == 1)
			return (create_token(TOKEN_REDIR_IN, value, state));
		else if (ft_strlen(value) == 2)
			return (create_token(TOKEN_HEREDOC, value, state));
		else
		{
			error("minishell: syntax error near unexpected token", value);
			return (create_token(TOKEN_ERROR, "", state));
		}
	}
	else if (**input == '>')
	{
		start = *input;
		while (**input == '>')
			(*input)++;
		value = strndup(start, *input - start);
		if (ft_strlen(value) == 1)
			return (create_token(TOKEN_REDIR_OUT, value, state));
		else if (ft_strlen(value) == 2)
			return (create_token(TOKEN_REDIR_APPEND, value, state));
		else
		{
			error("minishell: syntax error near unexpected token", value);
			return (create_token(TOKEN_ERROR, "", state));
		}
	}
	else if (**input == '&')
	{
		start = *input;
		while (**input == '&')
			(*input)++;
		value = strndup(start, *input - start);
		if (ft_strlen(value) == 1)
			return (create_token(TOKEN_WORD, value, state));
		else if (ft_strlen(value) == 2)
			return (create_token(TOKEN_AND, value, state));
		else
		{
			error("minishell: syntax error near unexpected token", value);
			return (create_token(TOKEN_ERROR, "", state));
		}
	}
	else if (**input == '(')
	{
		(*input)++;
		start = *input;
		nesting_level = 1;
		while (nesting_level > 0 && **input != '\0')
		{
			if (**input == '(')
				nesting_level++;
			else if (**input == ')')
				nesting_level--;
			(*input)++;
		}
		if (nesting_level == 0)
		{
			value = strndup(start, *input - start - 1);
			subshell_input = value;
			subshell_token = create_token(TOKEN_SUBSHELL, value, state);
			last_token = NULL;
			while ((token = get_next_token(&subshell_input))->type != TOKEN_EOF)
			{
				if (last_token == NULL)
					subshell_token->subtokens = token;
				else
					last_token->next = token;
				last_token = token;
			}
			return (subshell_token);
		}
		else
		{
			error("minishell: syntax error near unexpected token", value);
			return (create_token(TOKEN_ERROR, "", state));
		}
	}
	else if (**input == ')')
	{
		(*input)++;
		error("minishell: syntax error near unexpected token", value);
		return (create_token(TOKEN_ERROR, "", state));
	}
	else if (**input == '$')
	{
		(*input)++;
		if (**input == '?')
		{
			(*input)++;
			return (create_token(TOKEN_SPECIAL_VAR, "?", state));
		}
		else if (ft_isalnum(**input))
		{
			start = *input;
			while (ft_isalnum(**input))
				(*input)++;
			value = strndup(start, *input - start);
			if (state == NORMAL || state == IN_DQUOTES)
				return (create_token(TOKEN_ENV, value, state));
			else
				return (create_token(TOKEN_WORD, value, state));
		}
		else
		{
			(*input)--;
			start = *input;
			while (!isspace(**input) && !strchr("<>|&\"\'", **input))
				(*input)++;
			value = strndup(start, *input - start);
			return (create_token(TOKEN_WORD, value, state));
		}
	}
	else if (**input == '\'' || **input == '"')
	{
		quote_type = **input;
		if (**input == '\"')
			state = IN_DQUOTES;
		else
			state = IN_QUOTES;
		(*input)++;
		start = *input;
		while (**input != '\0')
		{
			if (**input == quote_type)
			{
				value = strndup(start, *input - start);
				(*input)++;
				return (create_token(TOKEN_WORD, value, state));
			}
			(*input)++;
		}
		error("Syntax error: unmatched quote", NULL);
		return (create_token(TOKEN_ERROR, "", state));
	}
	else
	{
		start = *input;
		while (!isspace(**input) && !strchr("<>|&\"\'", **input))
			(*input)++;
		value = strndup(start, *input - start);
		return (create_token(TOKEN_WORD, value, state));
	}
	return (create_token(TOKEN_UNKNOWN, "", state));
}

t_token	*tokenize(char *input)
{
	t_token	*head;
	t_token	*tail;
	t_token	*token;

	head = NULL;
	tail = NULL;
	while ((token = get_next_token(&input))->type != TOKEN_EOF)
	{
		if (token->type == TOKEN_ERROR)
		{
			// free_tokens(head);
			// free(token);
			return (NULL);
		}
		if (head == NULL)
			head = token;
		else
			tail->next = token;
		tail = token;
	}
	if (tail != NULL)
		tail->next = token;
	return (head);
}
