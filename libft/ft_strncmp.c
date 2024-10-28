/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazafin <arazafin@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:45:04 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/10/08 08:56:55 by arazafin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	len;

	len = 0;
	while (len < n && !((s1[len] == s2[len]) && !(s2[len])))
	{
		if (s1[len] != s2[len])
			return ((unsigned char)(s1[len]) - (unsigned char)s2[len]);
		len ++;
	}
	return (0);
}
