/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazafin <arazafin@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 10:40:58 by arazafin          #+#    #+#             */
/*   Updated: 2024/10/25 11:45:16 by arazafin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_redin(t_all *all)
{
	if (all->hd_file)
	{
		unlink(all->hd_file);
		free(all->hd_file);
		all->hd_file = NULL;
		all->exit_status = 130;
		return (1);
	}
	else if (all->infile)
	{
		all->sh++;
		if (check_file(all->infile, all, 0))
		{
			all->sh--;
			all->exit_status = 1;
			return (1);
		}
	}
	return (0);
}

int	check_redir(t_all *all, int *i, int *x, int *ret)
{
	if (!(*x))
	{
		is_need_pipe(all, i);
		all->outfile = get_outfile(all, *i);
		all->infile = get_infile(all, *i, ret);
		*x = 1;
		if (*ret == 2)
			return (2);
	}
	return (0);
}
