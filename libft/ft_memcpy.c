/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:44:14 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/02/21 13:10:08 by ntodisoa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	if ((dst == src) || n == 0)
		return (dst);
	if (!dst && !src)
		return (0);
	d = (char *)dst;
	s = (const char *)src;
	while (n--)
		d[n] = s[n];
	return (dst);
}
