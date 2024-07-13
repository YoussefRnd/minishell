/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 13:15:36 by yboumlak          #+#    #+#             */
/*   Updated: 2023/12/22 20:26:40 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;
	void	*new_content;

	new_list = NULL;
	while (lst)
	{
		new_content = f(lst->content);
		new_node = ft_lstnew(new_content);
		if (!new_node)
		{
			del(new_content);
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		lst = lst->next;
	}
	return (new_list);
}
/* 
void	*duplicate_string(void *content)
{
	return (ft_strdup((char *)content));
}

int	main(void)
{
	t_list	*head;
	t_list	*node1;
	t_list	*tmp;
	t_list	*new_list;

	node1 = ft_lstnew(ft_strdup("first"));
	head = node1;
	ft_lstadd_back(&head, ft_lstnew(ft_strdup("second")));
	ft_lstadd_back(&head, ft_lstnew(ft_strdup("third")));
	ft_lstadd_back(&head, ft_lstnew(ft_strdup("fourth")));
	tmp = head;
	while (tmp)
	{
		printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
	new_list = ft_lstmap(NULL, duplicate_string, free);
	tmp = new_list;
	while (tmp)
	{
		printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
	ft_lstclear(&head, free);
	ft_lstclear(&new_list, free);
	return (0);
}
 */