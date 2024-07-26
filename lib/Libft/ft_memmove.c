/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 17:29:46 by yboumlak          #+#    #+#             */
/*   Updated: 2023/12/10 23:48:51 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	n;

	if (!dst && !src)
		return (NULL);
	if (dst > src)
	{
		n = len;
		while (n > 0)
		{
			((unsigned char *)dst)[n - 1] = ((unsigned char *)src)[n - 1];
			n--;
		}
	}
	else
	{
		ft_memcpy(dst, src, len);
	}
	return (dst);
}
/*
int	main(void)
{
	char	src[10] = "Youssef";

	ft_memmove(src + 2, src, 5);
	printf("%s", src);
}
*/
