/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 15:06:53 by yboumlak          #+#    #+#             */
/*   Updated: 2023/12/22 17:20:47 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
}
/* 
int	main(void)
{
	t_list	*head;
	t_list	*node2;
	t_list	*node3;
	t_list	*last;

	node2 = ft_lstnew("node2");
	node3 = NULL;
	head = node2;
	ft_lstadd_back(&head, node3);
	last = ft_lstlast(head);
	printf("%s\n", last->content);
}
 */