/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:29:04 by yboumlak          #+#    #+#             */
/*   Updated: 2023/12/22 20:23:06 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (lst == NULL || f == NULL)
	{
		return ;
	}
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
/* 
void	print_content(void *content)
{
	printf("%s\n", (char *)content);
}

void	free_content(void *content)
{
	free(content);
}

int	main(void)
{
	t_list	*list;
	t_list	*node2;

	list = ft_lstnew(ft_strdup("node1"));
	node2 = ft_lstnew(ft_strdup("node2"));
	list->next = node2;
	ft_lstiter(list, print_content);
	ft_lstclear(&list, free_content);
	return (0);
}
 */