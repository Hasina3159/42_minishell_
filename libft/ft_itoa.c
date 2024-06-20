/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:43:31 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/02/23 15:39:00 by ntodisoa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static size_t	get_int_length(long n)
{
	long	i;
	size_t	len;

	i = 1;
	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = -n;
		len++;
	}
	while (i <= n)
	{
		i = i * 10;
		len++;
	}
	return (len);
}

static void	place_unity(long value, char *string, size_t i)
{
	if (i > 0)
		place_unity(value / 10, string, i - 1);
	if (i > 0 || (i == 0 && string[0] != '-'))
		string[i] = (value % 10) + '0';
}

char	*ft_itoa(int value)
{
	long	x;
	size_t	len;
	char	*final;

	x = (long) value;
	len = get_int_length(x);
	final = (char *)ft_calloc(len + 1, sizeof(char));
	if (final == NULL)
		return (NULL);
	if (x < 0)
	{
		final[0] = '-';
		x = -x;
	}
	place_unity(x, final, len - 1);
	final[len + 1] = 0;
	return (final);
}
