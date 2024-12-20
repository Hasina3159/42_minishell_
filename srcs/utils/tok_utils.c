/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:36:48 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/12/20 09:41:53 by ntodisoa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	i_n_op(int type)
{
	if (type == T_PIPE)
		return (1);
	else if (type == T_OR)
		return (1);
	else if (type == T_AND)
		return (1);
	return (0);
}

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
	else if (type == T_SPACE)
		return (1);
	return (0);
}

int	count_cmd(t_all *all)
{
	int	i;
	int	nb_cmd;

	i = 0;
	nb_cmd = 0;
	while (i < all->token_count && all->tokens[i].type != T_END)
	{
		if (all->tokens[i].type == T_COMMAND)
			nb_cmd++;
		i++;
	}
	return (nb_cmd);
}
