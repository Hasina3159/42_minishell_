/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_repl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:36:00 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/12/20 09:41:41 by ntodisoa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_count_occurences(char *text, char *sub)
{
	size_t	i;
	size_t	len;
	int		count;

	len = ft_strlen(text);
	i = 0;
	count = 0;
	while (i < len)
	{
		if (!ft_strncmp(&text[i], sub, ft_strlen(sub)))
			count++;
		i++;
	}
	return (count);
}

static int	ft_init(char *text, char *from, char *to, char **final)
{
	int		occ_count;
	size_t	len_final;

	occ_count = ft_count_occurences(text, from);
	len_final = ft_strlen(text) - (occ_count * ft_strlen(from)) + (occ_count
			* ft_strlen(to)) + 1;
	*final = (char *)malloc(sizeof(char) * len_final);
	*final[0] = 'a';
	if (*final == NULL)
		return (0);
	ft_bzero(*final, len_final + 1);
	return (1);
}

static void	ft_loop(char *final, char *to, size_t *j, size_t *k)
{
	*j = 0;
	while (*j < ft_strlen(to))
	{
		final[*k] = to[*j];
		*k = *k + 1;
		*j = *j + 1;
	}
}

static void	ft_free_and_assign(char **text, char **final)
{
	free(*text);
	*text = *final;
}

int	ft_str_repl(char *text, char *from, char *to)
{
	char	*final;
	size_t	i;
	size_t	j;
	size_t	k;

	final = NULL;
	if (!ft_init(text, from, to, &final))
		return (0);
	i = 0;
	k = 0;
	while (i < ft_strlen(text))
	{
		if (!ft_strncmp(&text[i], from, ft_strlen(from)))
		{
			ft_loop(final, to, &j, &k);
			i = i + ft_strlen(from);
			continue ;
		}
		else
			final[k] = text[i];
		i++;
		k++;
	}
	ft_free_and_assign(&text, &final);
	return (1);
}
