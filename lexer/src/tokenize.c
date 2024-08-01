/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 11:10:43 by yboumlak          #+#    #+#             */
/*   Updated: 2024/08/01 12:05:32 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lexer.h"

void	error(char *msg, char *token)
{
	printf("%s `%s'\n", msg, token);
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
		return (create_token(TOKEN_EOF, ft_strdup(""), state));
	if (ft_isspace(**input))
	{
		start = *input;
		while (ft_isspace(**input))
			(*input)++;
		value = ft_strndup(start, *input - start);
		return (create_token(TOKEN_WHITESPACE, value, state));
	}
	else if (**input == '|')
	{
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
			error("minishell: syntax error near unexpected token", value);
			return (create_token(TOKEN_ERROR, ft_strdup(""), state));
		}
	}
	else if (**input == '<')
	{
		start = *input;
		while (**input == '<')
			(*input)++;
		value = ft_strndup(start, *input - start);
		if (ft_strlen(value) == 1)
			return (create_token(TOKEN_REDIR_IN, value, state));
		else if (ft_strlen(value) == 2)
			return (create_token(TOKEN_HEREDOC, value, state));
		else
		{
			error("minishell: syntax error near unexpected token", value);
			return (create_token(TOKEN_ERROR, ft_strdup(""), state));
		}
	}
	else if (**input == '>')
	{
		start = *input;
		while (**input == '>')
			(*input)++;
		value = ft_strndup(start, *input - start);
		if (ft_strlen(value) == 1)
			return (create_token(TOKEN_REDIR_OUT, value, state));
		else if (ft_strlen(value) == 2)
			return (create_token(TOKEN_REDIR_APPEND, value, state));
		else
		{
			error("minishell: syntax error near unexpected token", value);
			return (create_token(TOKEN_ERROR, ft_strdup(""), state));
		}
	}
	else if (**input == '&')
	{
		start = *input;
		while (**input == '&')
			(*input)++;
		value = ft_strndup(start, *input - start);
		if (ft_strlen(value) == 1)
			return (create_token(TOKEN_WORD, value, state));
		else if (ft_strlen(value) == 2)
			return (create_token(TOKEN_AND, value, state));
		else
		{
			error("minishell: syntax error near unexpected token", value);
			return (create_token(TOKEN_ERROR, ft_strdup(""), state));
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
			value = ft_strndup(start, *input - start - 1);
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
			return (create_token(TOKEN_ERROR, ft_strdup(""), state));
		}
	}
	else if (**input == ')')
	{
		(*input)++;
		error("minishell: syntax error near unexpected token", value);
		return (create_token(TOKEN_ERROR, ft_strdup(""), state));
	}
	else if (**input == '$')
	{
		(*input)++;
		if (**input == '?')
		{
			(*input)++;
			return (create_token(TOKEN_SPECIAL_VAR, ft_strdup("?"), state));
		}
		else if (ft_isalnum(**input))
		{
			start = *input;
			while (ft_isalnum(**input))
				(*input)++;
			value = ft_strndup(start, *input - start);
			if (state == NORMAL || state == IN_DQUOTES)
				return (create_token(TOKEN_ENV, value, state));
			else
				return (create_token(TOKEN_WORD, value, state));
		}
		else
		{
			(*input)--;
			start = *input;
			while (!ft_isspace(**input) && !strchr("<>|&\"\'", **input))
				(*input)++;
			value = ft_strndup(start, *input - start);
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
				value = ft_strndup(start, *input - start);
				(*input)++;
				return (create_token(TOKEN_WORD, value, state));
			}
			(*input)++;
		}
		error("Syntax error: unmatched quote", NULL);
		return (create_token(TOKEN_ERROR, ft_strdup(""), state));
	}
	else
	{
		start = *input;
		while (!ft_isspace(**input) && !strchr("<>|&\"\'", **input))
			(*input)++;
		value = ft_strndup(start, *input - start);
		return (create_token(is_builtin(value), value, state));
	}
	return (create_token(TOKEN_UNKNOWN, ft_strdup(""), state));
}

t_token	*tokenize(char *input)
{
	t_token	*head;
	t_token	*tail;
	t_token	*token;

	head = NULL;
	tail = NULL;
	while (1)
	{
		token = get_next_token(&input);
		if (token == NULL)
			break ;
		if (token->type == TOKEN_ERROR)
		{
			free_tokens(&head);
			return (NULL);
		}
		if (token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT
			|| token->type == TOKEN_REDIR_APPEND
			|| token->type == TOKEN_HEREDOC)
		{
			token = get_next_token(&input);
			if (token == NULL || token->type != TOKEN_WORD)
			{
				error("minishell: syntax error near unexpected token",
					"newline");
				free_tokens(&head);
				return (NULL);
			}
		}
		if (head == NULL)
			head = token;
		else
			tail->next = token;
		tail = token;
		if (token->type == TOKEN_EOF)
			break ;
	}
	if (tail && (tail->type == TOKEN_AND || tail->type == TOKEN_PIPE
			|| tail->type == TOKEN_OR))
	{
		error("minishell: syntax error near unexpected token", tail->value);
		free_tokens(&head);
		return (NULL);
	}
	return (head);
}
