/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:44:19 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/02/21 13:08:12 by ntodisoa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	*s;
	unsigned char	tmp;

	tmp = c;
	s = (unsigned char *)str;
	i = 0;
	while (i < n)
	{
		s[i] = tmp;
		i++;
	}
	return (str);
}
