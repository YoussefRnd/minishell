/* *********************** *************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:43:18 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/07/19 13:21:56 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

#include "../../parser/inc/parser.h"
#include "../../utils/inc/utils.h"

// #include "../../exec/inc/execution.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

char				**split_it(char *str);
int	count_nodes(t_tree_node *current);
void				node_init(char *str, t_env *node);
void				append_node(t_env **head, char *data);
void				print_list(t_env *head);
void				find_and_remove(t_env **head_ref, char *key);
t_env				*create_env_dict(char **env);
int					node_exists(t_env **head_ref, char *key);
void modify_node(t_env **head_ref, char *key, char *new_value);
char **traverse_right_and_collect_values(t_tree_node *root, t_env **env, bool exp);
int respond_to_env(t_env *the_whole_list);
int respond_to_cd(t_tree_node *cmd, t_env **env);
int respond_to_b(t_tree_node *cmd, t_env **env);
int respond_to_export(t_env **list, t_tree_node *cmd);
int respond_to_unset(t_env **list, t_tree_node *cmd);
int	respond_to_pwd(void);
int respond_to_echo(t_tree_node *tree, t_env **env);
#endif