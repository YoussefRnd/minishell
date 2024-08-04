/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 11:10:43 by yboumlak          #+#    #+#             */
/*   Updated: 2024/08/03 19:28:22 by yboumlak         ###   ########.fr       */
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
		error("minishell: syntax error near unexpected token", value);
		return (create_token(TOKEN_ERROR, ft_strdup(""), state));
	}
}

t_token	*handle_redirection(char **input, char redir, t_quote state)
{
	char	*start;
	char	*value;

	start = *input;
	while (**input == redir)
		(*input)++;
	value = ft_strndup(start, *input - start);
	if (redir == '<')
	{
		if (ft_strlen(value) == 1)
			return (create_token(TOKEN_REDIR_IN, value, state));
		else if (ft_strlen(value) == 2)
			return (create_token(TOKEN_HEREDOC, value, state));
	}
	else if (redir == '>')
	{
		if (ft_strlen(value) == 1)
			return (create_token(TOKEN_REDIR_OUT, value, state));
		else if (ft_strlen(value) == 2)
			return (create_token(TOKEN_REDIR_APPEND, value, state));
	}
	error("minishell: syntax error near unexpected token", value);
	return (create_token(TOKEN_ERROR, ft_strdup(""), state));
}

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
	error("minishell: syntax error near unexpected token", value);
	return (create_token(TOKEN_ERROR, ft_strdup(""), state));
}

t_token	*handle_subshell(char **input, t_quote state)
{
	char	*start;
	int		nesting_level;
	char	*value;
	char	*subshell_input;
	t_token	*subshell_token;
	t_token	*last_token;
	t_token	*token;

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
		while (true)
		{
			token = get_next_token(&subshell_input);
			if (last_token == NULL)
				subshell_token->subtokens = token;
			else
				last_token->next = token;
			last_token = token;
			if (token->type == TOKEN_EOF)
				break ;
		}
		return (subshell_token);
	}
	else
	{
		error("minishell: syntax error near unexpected token", *input);
		return (create_token(TOKEN_ERROR, ft_strdup(""), state));
	}
}

t_token	*handle_dollar(char **input, t_quote state)
{
	char	*start;
	char	*value;

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

t_token	*handle_quote(char **input, t_quote *state)
{
	char	quote_type;
	char	*start;
	t_token	*temp_token;
	char	*value;

	quote_type = **input;
	*state = (**input == '"') ? IN_DQUOTES : IN_QUOTES;
	(*input)++;
	start = *input;
	temp_token = NULL;
	while (**input != '\0')
	{
		if (**input == '$' && *state == IN_DQUOTES)
		{
			(*input)--;
			temp_token = handle_dollar(input, *state);
			if (temp_token != NULL)
				return (temp_token);
		}
		if (**input == quote_type)
		{
			value = ft_strndup(start, *input - start);
			(*input)++;
			return (create_token(TOKEN_WORD, value, *state));
		}
		(*input)++;
	}
	error("Syntax error: unmatched quote", NULL);
	return (create_token(TOKEN_ERROR, ft_strdup(""), *state));
}

t_token	*handle_default(char **input, t_quote state)
{
	char	*start;
	char	*value;

	start = *input;
	while (!ft_isspace(**input) && !strchr("<>|&\"\'", **input))
		(*input)++;
	value = ft_strndup(start, *input - start);
	return (create_token(is_builtin(value), value, state));
}

t_token	*get_next_token(char **input)
{
	t_quote	state;

	state = NORMAL;
	if (**input == '\0')
		return (create_token(TOKEN_EOF, ft_strdup(""), state));
	if (ft_isspace(**input))
		return (handle_whitespace(input, state));
	else if (**input == '|')
		return (handle_pipe(input, state));
	else if (**input == '<' || **input == '>')
		return (handle_redirection(input, **input, state));
	else if (**input == '&')
		return (handle_ampersand(input, state));
	else if (**input == '(')
		return (handle_subshell(input, state));
	else if (**input == ')')
	{
		(*input)++;
		error("minishell: syntax error near unexpected token", *input);
		return (create_token(TOKEN_ERROR, ft_strdup(""), state));
	}
	else if (**input == '$')
		return (handle_dollar(input, state));
	else if (**input == '\'' || **input == '"')
		return handle_quote(input, &state);
	else
		return handle_default(input, state);
	return create_token(TOKEN_UNKNOWN, ft_strdup(""), state);
}

t_token	*tokenize(char *input)
{
	t_token	*head;
	t_token	*tail;
	t_token	*token;
	t_token	*last;

	head = NULL;
	tail = NULL;
	last = NULL;
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
		if (token->type != TOKEN_WHITESPACE && token->type != TOKEN_EOF)
			last = token;
		if (head == NULL)
			head = token;
		else
			tail->next = token;
		tail = token;
		if (token->type == TOKEN_EOF)
			break ;
	}
	if (last && (last->type == TOKEN_AND || last->type == TOKEN_PIPE
			|| last->type == TOKEN_OR))
	{
		error("minishell: syntax error near unexpected token", last->value);
		free_tokens(&head);
		return (NULL);
	}
	return (head);
}
