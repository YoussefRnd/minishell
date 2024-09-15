/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:42:38 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/09/15 13:43:29 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../../builtins/inc/builtins.h"
# include "../../inc/minishell.h"
# include "../../parser/inc/parser.h"

typedef struct s_norm
{
	t_token		*head;
	t_env		*envs;
	char		*input;
	t_token		*tokens;
	t_tree_node	*tree;
	bool		*forked;
}				t_norm;

void			_execute(t_tree_node *tree, t_env **env, bool *forked);
void			cmd_execute(t_tree_node *cmd, t_env **envps);
char			*find_path(char *file, char **arr);
char			*find_and_return_value(t_env *head_ref, char *key);
char			**examine(t_tree_node *head, char *path, t_env *env);
int				count_nodes(t_tree_node *current);
char			**to_arr(t_env *head);
void			free_n_set_to_null(char **v);
void			ft_free(char **splitted);
char			*ft_strcpy(char *dest, const char *src);
char			*ft_strcat(char *dest, const char *src);
int				count_nodes(t_tree_node *current);
void			operators_deal(t_tree_node *tree, t_env **env, bool *forked);
char			*get_value(t_env *env, char *key);
void			signal_handler_in_p(void);
void			signal_handler_in_c(void);
void			handle_exit_status(void);
void			ft_pipe(int *pfd);
void			ft_exit(int num);
void			pipes_deal(t_tree_node *tree, t_env **env, bool *forked);
void			words_deal(t_tree_node *tree, t_env **env, bool *forked);
void			subshells_deal(t_tree_node *tree, t_env **env, bool *forked);
void			envs_deal(t_tree_node *tree, t_env **env, bool *forked);
void			safe_free(char **ptr);
void			handle_redirections_if_present(t_tree_node *tree);
void			process_tok(t_tree_node *current, t_env *env);
void			left_side(t_tree_node *tree, t_env **env, bool *forked,
					int *pfd);
void			right_side(t_tree_node *tree, t_env **env, bool *forked,
					int *pfd);
int				its_a_directory(char *value);

#endif