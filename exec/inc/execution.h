/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:42:38 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/08/06 22:23:29 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

// #include "../../lexer/inc/lexer.h"
# include "../../builtins/inc/builtins.h"
# include "../../inc/minishell.h"
# include "../../parser/inc/parser.h"
// #include "../../parser/inc/parser.h"

void	_execute(t_tree_node *tree, t_env **env, bool *forked);
void	cmd_execute(t_tree_node *cmd, t_env **envps);
char	*find_path(char *file, char **arr);
char	*find_and_return_value(t_env *head_ref, char *key);
char	**examine(t_tree_node *head, char *path, t_env *env);
int		count_nodes(t_tree_node *current);
char	**to_arr(t_env *head);
void	free_n_set_to_null(char **v);
void	ft_free(char **splitted);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strcat(char *dest, const char *src);
int		count_nodes(t_tree_node *current);
void	operators_deal(t_tree_node *tree, t_env **env, bool *forked);
char	*get_value(t_env *env, char *key);
void	signal_handler_in_p(void);
void	signal_handler_in_c(void);
void    handle_exit_status();
void    ft_exit(int num);


#endif