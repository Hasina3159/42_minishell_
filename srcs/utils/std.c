/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:36:42 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/12/20 09:41:52 by ntodisoa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	new_std(char *nstd)
{
	int	fd;

	fd = open(nstd, O_RDWR);
	if (fd == -1)
	{
		perror("open");
		return ;
	}
	if (fd != STDIN_FILENO)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror("dup2");
			close(fd);
			return ;
		}
		close(fd);
	}
}
