/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 19:24:27 by yboumlak          #+#    #+#             */
/*   Updated: 2024/09/08 17:26:46 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lexer.h"

void	free_token(t_token **token)
{
	if (*token == NULL)
		return ;
	if ((*token)->subtokens != NULL)
	{
		free_tokens(&(*token)->subtokens);
		(*token)->subtokens = NULL;
	}
	if ((*token)->value != NULL)
	{
		free((*token)->value);
		(*token)->value = NULL;
	}
	free(*token);
	*token = NULL;
}

void	free_tokens(t_token **tokens)
{
	t_token	*next;
	t_token	*current;

	while (*tokens)
	{
		current = *tokens;
		next = current->next;
		if (current->subtokens != NULL)
		{
			free_tokens(&current->subtokens);
			current->subtokens = NULL;
		}
		if (current->value != NULL)
		{
			free(current->value);
			current->value = NULL;
		}
		*tokens = next;
		if (current != NULL)
		{
			free(current);
			current = NULL;
		}
	}
	*tokens = NULL;
}
