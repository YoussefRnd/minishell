/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 21:19:42 by yboumlak          #+#    #+#             */
/*   Updated: 2023/12/22 17:21:23 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst)
		return ;
	new->next = *lst;
	*lst = new;
}
/*
int	main(void)
{
	char	*str1;
	char	*str2;
	t_list	*node1;
	t_list	*node2;

	str1 = "Hello, world!";
	str2 = "Hello, Copilot!";
	node1 = ft_lstnew(str1);
	node2 = ft_lstnew(str2);
	ft_lstadd_front(&node1, node2);
	printf("First node content: %s\n", (char *)node1->content);
	printf("Second node content: %s\n", (char *)node1->next->content);
	free(node1->next);
	free(node1);
	return (0);
}
 */