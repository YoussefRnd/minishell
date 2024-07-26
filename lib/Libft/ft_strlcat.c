/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 21:56:53 by yboumlak          #+#    #+#             */
/*   Updated: 2023/12/10 23:49:13 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dst_len;

	dst_len = ft_strlen(dst);
	if (dstsize > 0 && dstsize > dst_len)
	{
		i = 0;
		while (i + dst_len < dstsize - 1 && src[i])
		{
			dst[i + dst_len] = src[i];
			i++;
		}
		dst[i + dst_len] = '\0';
		return (dst_len + ft_strlen(src));
	}
	return (dstsize + ft_strlen(src));
}
/*
int	main(void)
{
	char	src[10] = "youssef";
	char	dst[10] = "abcd";

	printf("%lu \n", ft_strlcat(dst, src, 0));
	printf("%s", dst);
}
*/
