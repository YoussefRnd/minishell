/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumlak <yboumlak@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:09:12 by yboumlak          #+#    #+#             */
/*   Updated: 2023/12/14 19:36:51 by yboumlak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	c;
	long	new_n;

	new_n = n;
	if (new_n < 0)
	{
		write(fd, "-", 1);
		new_n = -new_n;
	}
	if (new_n >= 10)
	{
		ft_putnbr_fd(new_n / 10, fd);
	}
	c = (new_n % 10) + '0';
	write(fd, &c, 1);
}
/*
int	main(void)
{
	ft_putnbr_fd(123555555, 1);
	write(1, "\n", 1);
	ft_putnbr_fd(-456, 1);
	write(1, "\n", 1);
	ft_putnbr_fd(0, 1);
	write(1, "\n", 1);
	return (0);
}
 */