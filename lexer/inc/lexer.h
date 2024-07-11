/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:01:12 by yboumlak          #+#    #+#             */
/*   Updated: 2024/07/11 19:22:03 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../../inc/minishell.h"

typedef enum s_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_EOFs
}					t_token_type;

typedef struct s_token
{
	t_token_type	token;
	char			*value;
}					t_token;

#endif