/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 11:04:42 by yboumlak          #+#    #+#             */
/*   Updated: 2024/08/04 17:29:12 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../../inc/minishell.h"

int		ft_isspace(char c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strndup(char *str, int n);
void	*ft_realloc(void *ptr, size_t size);
void	free_array(char **array);

#endif