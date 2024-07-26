/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:01:12 by yboumlak          #+#    #+#             */
/*   Updated: 2024/07/25 10:18:11 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../../inc/minishell.h"

typedef enum s_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_BACKGROUND,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC,
	TOKEN_SUBSHELL,
	TOKEN_EOF,
	TOKEN_UNKNOWN
}							t_token_type;

typedef struct s_token
{
	t_token_type			type;
	char					*value;
	struct s_token			*next;
	struct s_token			*subtokens;
}							t_token;

typedef struct s_redirection
{
	t_token_type			type;
	char					*file;
	char					*delimiter;
	struct s_redirection	*next;
}							t_redirection;

typedef struct s_tree_node
{
	t_token					*token;
	struct s_tree_node		*left;
	struct s_tree_node		*right;
	t_redirection		*redirections;
}							t_tree_node;

#endif