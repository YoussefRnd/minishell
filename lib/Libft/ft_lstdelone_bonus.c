/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 19:40:38 by yboumlak          #+#    #+#             */
/*   Updated: 2023/12/22 20:12:56 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst == NULL || del == NULL)
		return ;
	del(lst->content);
	free(lst);
}

/*
static void	free_content(void *content)
{
	free(content);
}

int	main(void)
{
	t_list	*head;
	t_list	*node;
	t_list	*node2;
	t_list	*current;

	node = ft_lstnew(strdup("first"));
	node2 = ft_lstnew(strdup("second"));
	head = node;
	node->next = node2;
	current = head;
	while (current != NULL)
	{
		printf("%s\n", current->content);
		current = current->next;
	}
	ft_lstdelone(node, free_content);
	head = node2;
	current = head;
	while (current != NULL)
	{
		printf("%s\n", current->content);
		current = current->next;
	}
	ft_lstdelone(node2, free_content);
}
 */