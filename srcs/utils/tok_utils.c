/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazafin <arazafin@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 13:56:55 by arazafin          #+#    #+#             */
/*   Updated: 2024/10/29 13:57:47 by arazafin         ###   ########.fr       */
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
