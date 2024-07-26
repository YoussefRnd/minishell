/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 11:17:44 by yboumlak          #+#    #+#             */
/*   Updated: 2023/12/20 14:27:22 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
		{
			return ((void *)(s) + i);
		}
		i++;
	}
	return (NULL);
}
/*
int	main(void)
{
	char	*s;
	char	c;

	s = "youssef";
	c = '\0';
	printf("%p \n", memchr(s, c, 6));
	printf("%p \n", ft_memchr(s, c, 6));
}
*/
