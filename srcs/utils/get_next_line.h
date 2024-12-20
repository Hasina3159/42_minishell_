/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 08:32:22 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/03/01 14:17:27 by ntodisoa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_file
{
	int		fd;
	char	buffer[BUFFER_SIZE + 1];
}			t_file;

void	get_ft_null_char(char *s);
size_t	get_ft_strlen(const char *s);
char	*get_ft_strchr(const char *s, int c);
char	*get_ft_strjoin(char *s1, char const *s2);
char	*get_ft_strdup(const char *s);
void	get_ft_strcpy(char *dst, const char *src);

#endif