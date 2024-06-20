/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:45:07 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/02/23 15:40:48 by ntodisoa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static void	condition(char big, char little, int *flag, int *j)
{
	if (big != little)
		*flag = 0;
	*j = *j + 1;
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	int		j;
	int		flag;

	if (little == big || (char)*little == '\0')
		return ((char *)big);
	i = 0;
	if ((char)*big == '\0')
		return (NULL);
	while (i + ft_strlen((char *)little) <= len)
	{
		j = 0;
		flag = 1;
		while (j < (int)ft_strlen((char *)little))
			condition((char)big[i + j], (char )little[j], &flag, &j);
		if (flag == 1)
			return ((char *)&big[i]);
		i ++;
	}
	return (NULL);
}
