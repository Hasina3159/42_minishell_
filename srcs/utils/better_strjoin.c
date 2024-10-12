/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   better_strjoin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazafin <arazafin@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 08:08:16 by arazafin          #+#    #+#             */
/*   Updated: 2024/10/08 08:08:17 by arazafin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*char	*better_strjoin(char *s1, char const *s2)
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
	free(s1);
	s1 = final;
	return (final);
}*/
char	*better_strjoin(char *s1, char const *s2)
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
	}
	while (s2[j])
	{
		final[i] = s2[j];
		i++;
		j++;
	}
	free(s1);
	s1 = final;
	return (final);
}
