/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:50:36 by yboumlak          #+#    #+#             */
/*   Updated: 2023/12/22 10:15:47 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbrlen(long n)
{
	int	len;

	if (n == 0)
		return (1);
	if (n < 0)
		n = -n;
	len = 0;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	nbr;
	int		len;

	nbr = n;
	len = ft_nbrlen(n);
	if (nbr < 0)
	{
		nbr *= -1;
		len++;
	}
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len--)
	{
		str[len] = nbr % 10 + '0';
		nbr /= 10;
	}
	if (n < 0)
	{
		str[0] = '-';
	}
	return (str);
}
/*
int	main(void)
{
	printf("%s", ft_itoa(-2147483648));
}
 */