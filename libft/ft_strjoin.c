/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:44:52 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/02/21 13:12:32 by ntodisoa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*final;

	len = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	final = (char *)ft_calloc(len + 1, sizeof(char));
	if (final == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		final[i] = s1[i];
		i++;
		j++;
	}
	i = 0;
	while (s2[i])
	{
		final[j] = s2[i];
		i++;
		j++;
	}
	return (final);
}
