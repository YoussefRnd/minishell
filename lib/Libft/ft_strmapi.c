/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:17:34 by yboumlak          #+#    #+#             */
/*   Updated: 2023/12/22 17:10:06 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	int		i;

	if (!s || !f)
		return (NULL);
	str = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
/* 
char	change_case(unsigned int i, char c)
{
	if (i % 2 == 0)
	{
		return (toupper(c));
	}
	else
	{
		return (tolower(c));
	}
}

int	main(void)
{
	char	*s;
	char	*result;

	s = "Youssef";
	result = ft_strmapi(s, NULL);
	printf("%s\n", result);
	free(result);
	return (0);
}
 */