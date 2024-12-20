/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:23:57 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/12/20 09:40:35 by ntodisoa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	env_size(t_env *env)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = env;
	while (tmp)
	{
		if (tmp->value == NULL)
		{
			tmp = tmp->next;
			continue ;
		}
		else
			i++;
		tmp = tmp->next;
	}
	return (i);
}

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
