/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:44:46 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/02/21 13:12:16 by ntodisoa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*final;
	int		i;
	int		len;

	len = ft_strlen((char *)s) + 1;
	final = (char *)ft_calloc(len, sizeof(char));
	if (final == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		final[i] = s[i];
		i++;
	}
	return (final);
}
