/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:41:46 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/02/21 14:01:43 by ntodisoa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_words(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static size_t	ft_get_length(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	**final;

	final = (char **)ft_calloc(ft_count_words(s, c) + 1, sizeof(char *));
	if (final == NULL)
		return (NULL);
	i = 0;
	j = -1;
	while (++j < ft_count_words(s, c))
	{
		while (s[i] && s[i] == c)
			i++;
		final[j] = (char *)ft_calloc(ft_get_length(&s[i], c) + 1, sizeof(char));
		if (final[j] == NULL)
			return (NULL);
		k = 0;
		while (s[i] && s[i] != c)
			final[j][k++] = s[i++];
	}
	final[j] = NULL;
	return (final);
}
