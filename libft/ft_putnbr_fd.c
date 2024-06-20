/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:44:28 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/02/21 13:08:46 by ntodisoa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putnbr(long n, int fd)
{
	char	c;

	if (n > 9)
		ft_putnbr(n / 10, fd);
	c = n % 10 + '0';
	ft_putchar_fd(c, fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	long	x;
	char	s;

	s = '-';
	x = (long) n;
	if (x < 0)
	{
		ft_putchar_fd(s, fd);
		x = -x;
	}
	ft_putnbr(x, fd);
}
