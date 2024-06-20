/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:45:09 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/02/23 11:29:41 by ntodisoa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*l;

	l = (char *)s;
	i = ft_strlen(s) - 1;
	if ((char)c == 0)
		return (&l[i + 1]);
	while (i >= 0)
	{
		if (l[i] == (char)c)
			return (&l[i]);
		i--;
	}
	return (NULL);
}
