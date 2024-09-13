/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 23:25:57 by yboumlak          #+#    #+#             */
/*   Updated: 2024/09/13 22:50:18 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lexer.h"

void	error(char *msg, char *token, int exit_status)
{
	status = exit_status;
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
