/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:31:45 by yboumlak          #+#    #+#             */
/*   Updated: 2024/09/15 22:01:45 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../../lexer/inc/lexer.h"
# include "../../utils/inc/utils.h"
# include <dirent.h>
# include <fcntl.h>
# include <stdbool.h>

typedef struct s_redirection
{
	t_token_type			type;
	char					*file;
	int						fd;
	char					*delimiter;
	struct s_redirection	*next;
}							t_redirection;

typedef struct s_tree_node
{
	t_token					*token;
	struct s_tree_node		*left;
	struct s_tree_node		*right;
	t_redirection			*redirections;
}							t_tree_node;

t_tree_node					*create_tree_node(t_token *token);

t_tree_node					*parse(t_token **tokens);
t_tree_node					*parse_and_or(t_token **tokens);
t_tree_node					*parse_pipe(t_token **tokens);
t_tree_node					*parse_command(t_token **tokens);
t_tree_node					*parse_subshell(t_token **tokens);

t_redirection				*parse_redirection(t_token **tokens);
void						attach_redirections(t_tree_node *node,
								t_redirection *redir);
void						here_doc(t_redirection *redir);
void						handle_heredoc(t_redirection *redir,
								t_token *file_token);
int							open_redirection_file(t_redirection *redir);

char						**expand_wildcard(char *pattern);

bool						is_valid_token(int token_type);
bool						is_env_token_attached(t_token **tokens);
bool						is_redirection_token(t_token **tokens);

void						concatenate_tokens_if_needed(t_token **tokens);

int							add_wildcard_token_to_tree(t_token **tokens,
								t_tree_node **node, t_tree_node **current);

char						**free_wildcards_on_error(char **matches, DIR *dir);
void						free_tree(t_tree_node **node);
void						free_redirections(t_redirection **redirection);

void						print_tree(t_tree_node *node, char *indent,
								bool is_last);

#endif