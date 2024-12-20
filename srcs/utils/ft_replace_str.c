/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:35:31 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/12/20 12:29:40 by ntodisoa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_replace_str(char **src, char *to)
{
	int		i;
	char	*s;
	char	*final;
	size_t	len;

	i = 0;
	while (*src[i])
	{
		if (*src[i] == '*')
		{
			s = *src;
			len = ft_strlen(*src) - 1 + ft_strlen(to);
			final = ft_calloc(len + 1,
					sizeof(char));
			ft_strlcpy(final, *src, i);
			ft_strlcpy(&final[i], to, ft_strlen(to) + 1);
			final[i + ft_strlen(to)] = 0;
			ft_strlcpy(&final[i + ft_strlen(to)],
				&s[i + 1], ft_strlen(&s[i + 1]) + 1);
			free(*src);
			*src = final;
			return ;
		}
		i++;
	}
}
