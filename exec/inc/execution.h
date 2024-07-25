/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:42:38 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/07/24 13:06:13 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
#define EXECUTION_H

// #include "../../lexer/inc/lexer.h"
#include "../../inc/minishell.h"
// #include "../../parser/inc/parser.h"

void cmd_execute(t_tree_node *cmd, t_env *envps);
void _execute(t_tree_node *tree);
void cmd_execute(t_tree_node *cmd, t_env *envps);
char	*find_path(char *file, char **arr);
char* find_and_return_value(t_env *head_ref, char *key);
char	**examine(t_tree_node *head);
int	count_nodes(t_tree_node *current);
char **to_arr(t_env *head);

#endif