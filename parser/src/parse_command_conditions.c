/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_conditions.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:22:23 by yboumlak          #+#    #+#             */
/*   Updated: 2024/09/15 21:56:35 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

bool	is_valid_token(int token_type)
{
	return (token_type != TOKEN_EOF && token_type != TOKEN_PIPE
		&& token_type != TOKEN_AND && token_type != TOKEN_OR);
}

bool	is_env_token_attached(t_token **tokens)
{
	return (((*tokens)->type == TOKEN_ENV && (*tokens)->next
			&& (*tokens)->next->type != TOKEN_WHITESPACE
			&& (*tokens)->next->type != TOKEN_EOF
			&& (*tokens)->next->type != TOKEN_EMPTY) || ((*tokens)->next
			&& (*tokens)->next->type == TOKEN_ENV)
		|| ((*tokens)->next->type == TOKEN_EMPTY
			&& (*tokens)->next->next->type == TOKEN_WORD));
}

bool	is_redirection_token(t_token **tokens)
{
	return ((*tokens)->type == TOKEN_REDIR_IN
		|| (*tokens)->type == TOKEN_REDIR_OUT
		|| (*tokens)->type == TOKEN_REDIR_APPEND
		|| (*tokens)->type == TOKEN_HEREDOC);
}
