/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:01:12 by yboumlak          #+#    #+#             */
/*   Updated: 2024/07/23 12:32:17 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../../inc/minishell.h"

typedef enum s_token_type
{
	TOKEN_WORD,
	TOKEN_WHITESPACE,
	TOKEN_PIPE,
	TOKEN_BACKGROUND,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC,
	TOKEN_SUBSHELL,
	TOKEN_ENV,
	TOKEN_SPECIAL_VAR,
	TOKEN_EOF,
	TOKEN_UNKNOWN
}					t_token_type;

typedef enum s_quote
{
	NORMAL,
	IN_QUOTES,
	IN_DQUOTES,
}					t_quote;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
	struct s_token	*subtokens;
	t_quote			state;
}					t_token;

t_token				*tokenize(char *input);

#endif