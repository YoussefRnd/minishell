/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 11:10:43 by yboumlak          #+#    #+#             */
/*   Updated: 2024/09/15 22:11:10 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lexer.h"

t_token	*handle_close_paren(char **input, t_quote state)
{
	(*input)++;
	error("minishell: syntax error near unexpected token", *input, 258);
	return (create_token(TOKEN_ERROR, ft_strdup(""), state));
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
		return (handle_close_paren(input, state));
	else if (**input == '$')
		return (handle_dollar(input, state));
	else if (**input == '\'' || **input == '"')
		return (handle_quote(input, &state));
	else
		return (handle_default(input, state));
	return (create_token(TOKEN_UNKNOWN, ft_strdup(""), state));
}

int	process_token(t_token *token, t_token **head, t_token **tail,
		t_token **last)
{
	t_token	*current_token;

	current_token = token;
	while (current_token)
	{
		if (*head == NULL)
			*head = current_token;
		else
			(*tail)->next = current_token;
		*tail = current_token;
		if (current_token->type == TOKEN_ERROR)
		{
			free_tokens(head);
			return (0);
		}
		if (current_token->type != TOKEN_WHITESPACE
			&& current_token->type != TOKEN_EOF)
			*last = current_token;
		current_token = current_token->next;
	}
	return (1);
}

t_token	*check_token_syntax(t_token *head, t_token *last)
{
	if (head && (head->type == TOKEN_AND || head->type == TOKEN_PIPE
			|| head->type == TOKEN_OR))
	{
		error("minishell: syntax error near unexpected token", head->value,
			258);
		free_tokens(&head);
		return (NULL);
	}
	if (last && (last->type == TOKEN_AND || last->type == TOKEN_PIPE
			|| last->type == TOKEN_OR))
	{
		error("minishell: syntax error near unexpected token", last->value, 1);
		free_tokens(&head);
		return (NULL);
	}
	if (check_token_sequence(head))
	{
		free_tokens(&head);
		return (NULL);
	}
	return (head);
}

t_token	*tokenize(char *input)
{
	t_token	*head;
	t_token	*tail;
	t_token	*last;
	t_token	*token;

	head = NULL;
	tail = NULL;
	last = NULL;
	while (1)
	{
		token = get_next_token(&input);
		if (!process_token(token, &head, &tail, &last))
			return (NULL);
		if (token->type == TOKEN_EOF)
			break ;
	}
	return (check_token_syntax(head, last));
}
