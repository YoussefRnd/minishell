/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 12:59:08 by yboumlak          #+#    #+#             */
/*   Updated: 2023/12/10 23:49:31 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needle_size;

	needle_size = ft_strlen(needle);
	if (!*needle)
		return ((char *)haystack);
	while (*haystack && len >= needle_size)
	{
		if (ft_strncmp(haystack, needle, needle_size) == 0)
			return ((char *)haystack);
		haystack++;
		len--;
	}
	return (NULL);
}
/*
int	main(void)
{
	char	*s;
	char	*n;

	s = "youssef";
	n = "ss";
	printf("%s", ft_strnstr(s, n, 6));
	printf("%s", strnstr(s, n, 1));
}
*/
