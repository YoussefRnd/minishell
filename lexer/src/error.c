/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrahimi <hbrahimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 23:25:57 by yboumlak          #+#    #+#             */
/*   Updated: 2024/09/15 22:00:35 by hbrahimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lexer.h"

void	error(char *msg, char *token, int exit_status)
{
	g_status = exit_status;
	printf("%s `%s'\n", msg, token);
}

bool	check_token_sequence(t_token *head)
{
	t_token	*current;

	current = head;
	while (current)
	{
		if (current->type == TOKEN_PIPE || current->type == TOKEN_AND
			|| current->type == TOKEN_OR)
		{
			if (current->next->next && (current->next->next->type == TOKEN_PIPE
					|| current->next->next->type == TOKEN_AND
					|| current->next->next->type == TOKEN_OR))
			{
				error("minishell: syntax error near unexpected token",
					current->next->next->value, 258);
				return (true);
			}
		}
		current = current->next;
	}
	return (false);
}
