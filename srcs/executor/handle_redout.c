/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redout.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:24:48 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/12/06 10:24:49 by ntodisoa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	open_outfile(t_all *all, int type)
{
	int	fd;

	fd = -1;
	if (type == 1)
		fd = open(all->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	else if (type == 2)
		fd = open(all->outfile, O_CREAT | O_WRONLY | O_APPEND, 0777);
	return (fd);
}

int	f_op(int type)
{
	if (type == T_PIPE || type == T_END || type == T_OR || type == T_AND)
		return (1);
	return (0);
}

static char	*checkout(t_all *all, int x, int *check)
{
	int		fd;
	char	*out;

	out = all->tokens[x + 1].value;
	fd = open(out, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (check_file(out, all, 1))
	{
		*check = 1;
		return (out);
	}
	ft_putchar_fd('\0', fd);
	close(fd);
	all->out_type = 1;
	return (out);
}

char	*get_outfile(t_all *all, int i)
{
	char	*out;
	int		check;
	int		x;
	int		fd;

	out = NULL;
	check = 0;
	x = i;
	all->out_type = 0;
	while (!f_op(all->tokens[x].type))
	{
		if (all->tokens[x].type == T_OUT && !check)
			out = checkout(all, x, &check);
		else if (all->tokens[x].type == T_OUT_APPEND && !check)
		{
			out = all->tokens[x + 1].value;
			fd = open(out, O_CREAT | O_WRONLY | O_APPEND, 0777);
			if (check_file(out, all, 1))
				check = 1;
			close(fd);
			all->out_type = 2;
		}
		x++;
	}
	return (out);
}

int	handle_redout(t_all *all)
{
	int	out;

	if (check_file(all->outfile, all, 1))
	{
		close(all->fd[0]);
		close(all->fd[1]);
		return (1);
	}
	out = open_outfile(all, all->out_type);
	if (dup2(out, STDOUT_FILENO) == -1)
	{
		perror("dup2 fd[1] to stdout");
		exit(1);
	}
	close(out);
	close(all->fd[0]);
	close(all->fd[1]);
	return (0);
}
