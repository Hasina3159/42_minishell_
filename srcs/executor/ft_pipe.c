/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazafin <arazafin@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 11:16:23 by arazafin          #+#    #+#             */
/*   Updated: 2024/09/29 14:03:23 by arazafin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	pipeline_in(t_all *all)
{
	if (dup2(all->tmp, STDIN_FILENO) == -1)
	{
		perror("dup2 tmp to stdin");
		exit(1);
	}
	close(all->tmp);
}

void	pipeline_out(t_all *all)
{
	if (dup2(all->fd[1], STDOUT_FILENO) == -1)
	{
		perror("dup2 fd[1] to stdout");
		exit(1);
	}
	close(all->fd[1]);
	close(all->fd[0]);
}

int	ft_pipe(t_all *all)
{
	if (all->has_in)
	{
		if (handle_redin(all))
			return (1);
	}
	else if (all->tmp != -1)
	{
		pipeline_in(all);
	}
	if (all->has_out)
	{
		if (handle_redout(all))
			return (1);
	}
	else if (all->has_pipe)
	{
		pipeline_out(all);
	}
	else
	{
		close(all->fd[0]);
		close(all->fd[1]);
	}
	return (0);
}
