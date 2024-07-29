/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:31:45 by yboumlak          #+#    #+#             */
/*   Updated: 2024/07/29 09:48:49 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../../lexer/inc/lexer.h"
# include "../../utils/inc/utils.h"
# include <stdbool.h>
# include <fcntl.h>

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
	char					**args;
}							t_tree_node;

t_tree_node					*parse(t_token **tokens);
void						print_tree(t_tree_node *node, char *indent,
								bool is_last);

#endif