/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:43:18 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/09/14 15:40:02 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../../parser/inc/parser.h"
# include "../../utils/inc/utils.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

char				**split_it(char *str);
int					count_nodes(t_tree_node *current);
int					node_init(char *str, t_env *node);
void				append_node(t_env **head, char *data);
void				print_list(t_env *head);
void				find_and_remove(t_env **head_ref, char *key);
t_env				*create_env_dict(char **env);
int					node_exists(t_env **head_ref, char *key);
void				find_and_modify(t_env **head_ref, char *key,
						char *new_value);
char				**traverse_right_and_collect_values(t_tree_node *root,
						t_env **env, bool exp);
int					respond_to_env(t_env *the_whole_list, t_tree_node *cmd);
int					respond_to_cd(t_tree_node *cmd, t_env **env);
int					respond_to_b(t_tree_node *cmd, t_env **env);
int					respond_to_export(t_env **list, t_tree_node *cmd);
int					respond_to_unset(t_env **list, t_tree_node *cmd);
int					respond_to_pwd(t_tree_node *cmd);
bool				flag_is_valid(char *str);
int					count_nodes_env(t_env *head);
int					respond_to_echo(t_tree_node *tree, t_env **env);
int					respond_to_exit(t_tree_node *cmd_args, t_env **env);
int					handle_redir(t_redirection *current);
char				*get_value(t_env *env, char *key);
void				free_redirections(t_redirection **redirection);
void				safe_free(char **ptr);
void				free_env_list(t_env **head_ref);
char				*find_and_return_value(t_env *head_ref, char *key);
int					is_valid_env_var_name(const char *key);
void				update_current_token_value(t_tree_node *current,
						char **copy);
void				remove_node(t_tree_node **head,
						t_tree_node *node_to_remove);
void				traverse_and_expand(t_tree_node *tree, t_env *env);
void				print_list_exp(t_env *list);
char				**allocate_array(t_tree_node *head, char *path);
char				**allocate_array_env(int count);
void				fill_array(char **array, t_tree_node *root, t_env **env,
						bool exp);
void				handle_duplication_and_close(int out, int in);

#endif