/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:43:18 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/07/19 10:19:30 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

char				**split_it(char *str);
void				node_init(char *str, t_env *node);
void				append_node(t_env **head, char *data);
void				print_list(t_env *head);
void find_and_remove(t_env **head_ref, char *key);
t_env				*create_env_dict(char **env);
int					ft_strcmp(char *s1, char *s2);

#endif