/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 19:24:27 by yboumlak          #+#    #+#             */
/*   Updated: 2024/07/30 11:18:11 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lexer.h"

void	free_tokens(t_token **tokens)
{
	t_token	*next;
	t_token	*current;

	while (*tokens)
	{
		current = *tokens;
		next = current->next;
		free_tokens(&current->subtokens);
		current->subtokens = NULL;
		free(current->value);
		current->value = NULL;
		*tokens = next;
		free(current);
		current = NULL;
	}
	*tokens = NULL;
}
