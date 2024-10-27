/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazafin <arazafin@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:15:09 by arazafin          #+#    #+#             */
/*   Updated: 2024/10/24 14:19:44 by arazafin         ###   ########.fr       */
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
