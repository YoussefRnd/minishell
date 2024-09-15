/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concatenate_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 19:15:07 by yboumlak          #+#    #+#             */
/*   Updated: 2024/09/15 21:31:13 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"

void	concatenate_tokens_if_needed(t_token **tokens)
{
	t_token	*next;
	char	*value;

	while ((*tokens)->next && ((*tokens)->next->type == TOKEN_WORD
			|| (*tokens)->next->type == TOKEN_WILDCARD
			|| ((*tokens)->next->type == TOKEN_EMPTY
				&& (*tokens)->type != TOKEN_ENV)) && (*tokens)->is_atached != 1)
	{
		value = ft_strjoin((*tokens)->value, (*tokens)->next->value);
		free((*tokens)->value);
		(*tokens)->value = value;
		if ((*tokens)->next->type == TOKEN_WILDCARD)
			(*tokens)->type = TOKEN_WILDCARD;
		next = (*tokens)->next;
		(*tokens)->next = next->next;
		free(next);
	}
}
