/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 11:10:43 by yboumlak          #+#    #+#             */
/*   Updated: 2024/07/22 19:41:36 by yboumlak         ###   ########.fr       */
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
	return (token);
}

t_token	*get_next_token(char **input)
{
	char	*start;
	char	*value;
	int		open_parentheses;
	int		nesting_level;
	char	*subshell_input;
	t_token	*subshell_token;
	t_token	*last_token;
	t_token	*token;
	t_quote	state;
	char	quote_type;
	int		quote_count;
	t_quote	quote_state;
	int		unattached_quote;

	state = NORMAL;
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
		if (*(*input + 1) == '|')
		{
			(*input) += 2;
			return (create_token(TOKEN_OR, "||", state));
		}
		(*input)++;
		return (create_token(TOKEN_PIPE, "|", state));
	}
	else if (**input == '<')
	{
		if (*(*input + 1) == '<')
		{
			(*input) += 2;
			return (create_token(TOKEN_HEREDOC, "<<", state));
		}
		(*input)++;
		return (create_token(TOKEN_REDIR_IN, "<", state));
	}
	else if (**input == '>')
	{
		if (*(*input + 1) == '>')
		{
			(*input) += 2;
			return (create_token(TOKEN_REDIR_APPEND, ">>", state));
		}
		(*input)++;
		return (create_token(TOKEN_REDIR_OUT, ">", state));
	}
	else if (**input == '&')
	{
		if (*(*input + 1) == '&')
		{
			(*input) += 2;
			return (create_token(TOKEN_AND, "&&", state));
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
			fprintf(stderr, "Syntax error: missing closing parenthesis\n");
			return (create_token(TOKEN_UNKNOWN, "", state));
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
		fprintf(stderr, "Syntax error: unmatched quote\n");
		return (create_token(TOKEN_UNKNOWN, "", state));
	}
	else if (**input == '$')
	{
		(*input)++;
		if (**input == '(')
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
				subshell_token = create_token(TOKEN_ENV, value, state);
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
				fprintf(stderr, "Syntax error: missing closing parenthesis\n");
				return (create_token(TOKEN_UNKNOWN, "", state));
			}
		}
		else
		{
			start = *input;
			while (!isspace(**input) && !strchr("<>|&\"\'", **input))
				(*input)++;
			value = strndup(start, *input - start);
			return (create_token(TOKEN_ENV, value, state));
		}
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
