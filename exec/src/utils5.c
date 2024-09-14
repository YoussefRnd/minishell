/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:18:44 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/09/14 18:21:02 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../parser/inc/parser.h"
#include "../inc/execution.h"

int	its_a_directory(char *value)
{
	DIR	*dir;

	dir = opendir(value);
	if (dir)
	{
		closedir(dir);
		perror("it is a directory");
		return (1);
	}
	else
		return (0);
}
