/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 23:25:57 by yboumlak          #+#    #+#             */
/*   Updated: 2024/09/04 23:26:01 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lexer.h"

void	error(char *msg, char *token, int exit_status)
{
	status = exit_status;
	printf("%s `%s'\n", msg, token);
}
