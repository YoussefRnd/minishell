/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 12:54:19 by yboumlak          #+#    #+#             */
/*   Updated: 2023/12/16 15:00:15 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}
/*
int	main(void)
{
	t_list	*node1;
	t_list	*node2;
	t_list	*node3;
	t_list	*last;

	node1 = ft_lstnew("youssef");
	node2 = ft_lstnew("boumlaki");
	node3 = ft_lstnew("idk");
	node1->next = node2;
	node2->next = node3;
	last = ft_lstlast(node1);
	printf("%s\n", last->content);
}
 */