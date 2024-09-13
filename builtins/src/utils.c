/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 09:49:45 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/09/12 17:21:18 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../exec/inc/execution.h"
#include "../../inc/minishell.h"
#include "../inc/builtins.h"

char	**allocate_memory_for_split(void)
{
	return (ft_calloc(sizeof(char *), 3));
}

int	calculate_key_length(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		i++;
	}
	return (i);
}

int	calculate_value_length(char *str, int start_index)
{
	int	i;

	i = start_index;
	while (str[i])
	{
		i++;
	}
	return (i - start_index);
}

void	assign_values_to_array(char **that, char *str, int key_len,
		int value_len)
{
	if (str[key_len] && str[key_len] == '=' && !str[key_len + 1])
		that[1] = ft_strdup("");
	else
		that[1] = ft_substr(str, key_len + 1, value_len);
	that[0] = ft_substr(str, 0, key_len);
	that[2] = NULL;
}

char	**split_it(char *str)
{
	int		key_len;
	int		value_len;
	char	**that;

	if (!str)
		return (NULL);
	that = allocate_memory_for_split();
	key_len = calculate_key_length(str);
	value_len = calculate_value_length(str, key_len);
	assign_values_to_array(that, str, key_len, value_len);
	return (that);
}
