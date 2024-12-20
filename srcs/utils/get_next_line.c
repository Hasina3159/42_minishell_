/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 08:32:25 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/12/20 09:41:43 by ntodisoa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	get_ft_null_char(char *s)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return ;
	while (s[i])
	{
		s[i] = 0;
		i++;
	}
}

static int	get_ft_cond(char *file, int *x, char **final, int fd)
{
	*x = read(fd, file, BUFFER_SIZE);
	if (*x > 0)
	{
		get_ft_null_char(&file[*x]);
		*final = get_ft_strjoin(*final, file);
		return (1);
	}
	return (0);
}

static char	*get_ft_read_line(char *file, char *tmp1, int x, int fd)
{
	char	*final;

	final = get_ft_strdup(file);
	if (BUFFER_SIZE == 0 || fd < 0)
		return (free(final), NULL);
	while (!get_ft_strchr(final, '\n') && get_ft_cond(file, &x, &final, fd))
		continue ;
	if (final == NULL)
		return (NULL);
	if (!*final)
		return (free(final), NULL);
	tmp1 = get_ft_strchr(file, '\n');
	if (tmp1)
	{
		get_ft_null_char(get_ft_strchr(final, '\n') + 1);
		get_ft_strcpy(file, &tmp1[1]);
	}
	else
		get_ft_null_char(file);
	return (final);
}

char	*get_next_line(int fd)
{
	static char	file[BUFFER_SIZE];
	int			x;
	char		*tmp1;
	char		*final;

	tmp1 = NULL;
	x = 0;
	final = get_ft_read_line(file, tmp1, x, fd);
	free(tmp1);
	return (final);
}
