/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 15:23:39 by yboumlak          #+#    #+#             */
/*   Updated: 2023/12/22 17:12:06 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	size_t	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
/* 
void	change_case(unsigned int i, char *c)
{
	if (i % 2 == 0)
	{
		*c = toupper(*c);
	}
	else
	{
		*c = tolower(*c);
	}
}

int	main(void)
{
	char	*s;

	s = "Youssef";
	ft_striteri(s, NULL);
	printf("%s", s);
}
 */