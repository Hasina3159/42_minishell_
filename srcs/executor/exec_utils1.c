/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazafin <arazafin@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 11:33:32 by arazafin          #+#    #+#             */
/*   Updated: 2024/10/21 10:18:29 by arazafin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_n_op(int type)
{
	if (type == T_PIPE)
		return (1);
	else if (type == T_OR)
		return (1);
	else if (type == T_AND)
		return (1);
	else if (type == T_END)
		return (1);
	return (0);
}

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
	while (j > 0 && (all->tokens[j].type == T_FILE_IN
			|| all->tokens[j].type == T_IN || all->tokens[j].type == T_COMMAND
			|| all->tokens[j].type == T_WORD))
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
