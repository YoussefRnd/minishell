/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 20:49:33 by yboumlak          #+#    #+#             */
/*   Updated: 2023/12/18 15:02:36 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*m;
	size_t	i;

	m = (void *)malloc(count * size);
	if (m != NULL)
	{
		i = 0;
		while (i < count * size)
		{
			((char *)m)[i] = 0;
			i++;
		}
	}
	return (m);
}
/*
int	main(void)
{
	char	*m;

	m = ft_calloc(3, sizeof(char));
	for (size_t i = 0; i < sizeof(m); i++)
	{
		printf("%hhd", m[i]);
	}
	return (0);
}
 */