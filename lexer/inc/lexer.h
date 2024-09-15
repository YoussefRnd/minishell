/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:01:12 by yboumlak          #+#    #+#             */
/*   Updated: 2024/09/15 22:09:38 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../../inc/minishell.h"
# include "../../utils/inc/utils.h"

typedef enum s_token_type
{
	TOKEN_WORD,
	TOKEN_WHITESPACE,
	TOKEN_PIPE,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC,
	TOKEN_SUBSHELL,
	TOKEN_ENV,
	TOKEN_SPECIAL_VAR,
	TOKEN_BUILTIN,
	TOKEN_WILDCARD,
	TOKEN_EMPTY,
	TOKEN_EOF,
	TOKEN_UNKNOWN,
	TOKEN_ERROR
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
	bool			is_atached;
}					t_token;

typedef struct s_quote_state
{
	t_token			*head_token;
	t_token			*last_token;
	char			*start;
}					t_quote_state;

t_token				*tokenize(char *input);
t_token				*get_next_token(char **input);
t_token				*create_token(t_token_type type, char *value,
						t_quote state);
void				free_tokens(t_token **head);
void				free_token(t_token **token);
void				error(char *msg, char *token, int exit_status);
bool				check_token_sequence(t_token *head);

t_token				*handle_dollar(char **input, t_quote state);

t_token				*handle_quote(char **input, t_quote *state);
t_token				*handle_non_alnum(char **input, t_quote state);
t_token				*handle_env_digit(char **input, t_quote state);

t_token				*handle_subshell(char **input, t_quote state);

t_token				*handle_pipe(char **input, t_quote state);

t_token				*handle_ampersand(char **input, t_quote state);

t_token				*handle_redirection(char **input, char redir,
						t_quote state);

t_token				*handle_whitespace(char **input, t_quote state);

t_token				*handle_default(char **input, t_quote state);

#endif