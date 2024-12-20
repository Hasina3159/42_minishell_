/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:36:12 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/12/20 09:41:42 by ntodisoa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_strndup(const char *s, int len)
{
	char	*final;
	int		i;

	final = (char *)ft_calloc(len + 1, sizeof(char));
	if (final == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		final[i] = s[i];
		i++;
	}
	return (final);
}
