/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 21:16:20 by yboumlak          #+#    #+#             */
/*   Updated: 2023/12/22 16:11:43 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed_s;
	size_t	start;
	size_t	end;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
	{
		start++;
	}
	end = ft_strlen(s1);
	while (end > start && ft_strchr(set, s1[end - 1]))
	{
		end--;
	}
	trimmed_s = (char *)malloc((end - start + 1) * sizeof(char));
	if (!trimmed_s)
		return (NULL);
	ft_strlcpy(trimmed_s, s1 + start, end - start + 1);
	return (trimmed_s);
}
/* 
int	main(void)
{
	char	*s;
	char	*set;

	s = "kkshfdhfhkfoisjkkkkkkkk";
	set = "kk";
	printf("%s", ft_strtrim(s, set));
}
 */