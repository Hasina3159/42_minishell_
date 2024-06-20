/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:44:44 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/02/23 13:46:23 by ntodisoa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*l;

	i = 0;
	l = (char *)s;
	while (l[i])
	{
		if (l[i] == (char)c)
			return (&l[i]);
		i++;
	}
	if ((char)c == 0)
		return (&l[i]);
	return (NULL);
}
