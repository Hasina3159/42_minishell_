/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:24:42 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/12/20 09:40:40 by ntodisoa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_file(char *file, t_all *all, int f)
{
	if (f == 0)
	{
		if (access(file, F_OK) < 0)
		{
			if (all->sh)
				print_error(NULL, file, "No such file or directory");
			return (1);
		}
		if (access(file, R_OK) < 0)
		{
			if (all->sh)
				print_error(NULL, file, "Permission denied");
			return (1);
		}
	}
	else if (f == 1)
	{
		if (access(file, W_OK) < 0)
		{
			if (all->sh)
				print_error(NULL, file, "Permission denied");
			return (1);
		}
	}
	return (0);
}

static char	*checkin(t_all *all, int x, int *check)
{
	char	*in;

	in = NULL;
	if (all->hd_file)
	{
		unlink(all->hd_file);
		free(all->hd_file);
		all->hd_file = NULL;
	}
	in = all->tokens[x + 1].value;
	if (check_file(all->tokens[x + 1].value, all, 0))
		*check = 1;
	return (in);
}

static void	check_hd_file(t_all *all)
{
	if (all->hd_file)
	{
		unlink(all->hd_file);
		free(all->hd_file);
		all->hd_file = NULL;
	}
}

char	*get_infile(t_all *all, int i, int *stat)
{
	char	*in;
	int		check;
	int		x;

	in = NULL;
	check = 0;
	x = i;
	while (!f_op(all->tokens[x].type))
	{
		if (all->tokens[x].type == T_HD && !check)
		{
			check_hd_file(all);
			*stat = heredoc(all, all->tokens[x + 1]);
			in = all->hd_file;
			if (*stat == 2)
				break ;
		}
		else if (all->tokens[x].type == T_IN && !check)
			in = checkin(all, x, &check);
		x++;
	}
	return (in);
}

int	handle_redin(t_all *all)
{
	int	in;

	if (all->tmp != -1)
		close(all->tmp);
	if (check_file(all->infile, all, 0))
	{
		close(all->fd[0]);
		close(all->fd[1]);
		return (1);
	}
	in = open(all->infile, O_RDONLY);
	if (dup2(in, STDIN_FILENO) == -1)
	{
		perror("dup2 tmp to stdin");
		exit(1);
	}
	close(in);
	if (all->hd_file)
	{
		if (!ft_strncmp(all->infile, all->hd_file, ft_strlen(all->infile)))
			unlink(all->hd_file);
		free(all->hd_file);
		all->hd_file = NULL;
	}
	return (0);
}
