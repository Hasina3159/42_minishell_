/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:23:38 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/12/06 10:23:39 by ntodisoa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	is_need_pipe(t_all *all, int *i)
{
	int	j;
	int	type;

	j = *i;
	while (!is_n_op(all->tokens[j].type))
	{
		type = all->tokens[j].type;
		if (type == T_OUT || type == T_OUT_APPEND)
			all->has_out = 1;
		if (type == T_HD || type == T_IN)
			all->has_in = 1;
		j++;
	}
	if (all->tokens[j].type == T_PIPE)
		all->has_pipe = 1;
}

int	ft_has_op_before(t_all *all, int *i, int type)
{
	int	j;

	j = *i;
	while (j > 0 && !i_n_op(all->tokens[j].type))
		j--;
	if (all->tokens[j].type == type)
		return (1);
	return (0);
}

void	reset_redirection(t_all *all, int *x)
{
	*x = 0;
	all->has_in = 0;
	all->has_pipe = 0;
	all->has_out = 0;
}

int	ft_has_op_after(t_all *all, int *i)
{
	int	j;

	j = *i;
	while (!is_n_op(all->tokens[j].type))
		j++;
	if (all->tokens[j].type == T_AND || all->tokens[j].type == T_OR)
		return (1);
	return (0);
}
