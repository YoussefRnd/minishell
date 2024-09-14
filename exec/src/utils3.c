/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:25:46 by hbrahimi          #+#    #+#             */
/*   Updated: 2024/09/14 15:54:17 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../parser/inc/parser.h"
#include "../inc/execution.h"

char	*ft_strcpy(char *dest, const char *src)
{
	char	*save;
	int		i;

	save = dest;
	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (save);
}

char	*ft_strcat(char *dest, const char *src)
{
	char	*rdest;
	int		i;

	rdest = dest;
	while (*dest)
	{
		dest++;
	}
	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (rdest);
}

void	ft_exit(int num)
{
	g_status = num;
	exit(EXIT_FAILURE);
}

void	handle_exit_status(void)
{
	if (WIFEXITED(g_status))
	{
		g_status = WEXITSTATUS(g_status);
	}
	else if (WIFSIGNALED(g_status))
	{
		g_status = 128 + WTERMSIG(g_status);
	}
}

void	ft_pipe(int *pfd)
{
	if (pipe(pfd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}
