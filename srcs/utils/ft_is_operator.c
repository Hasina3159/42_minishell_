/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:33:45 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/12/06 10:33:46 by ntodisoa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_is_operator(char c)
{
	if (c == '|' || c == '&' || c == '<' || c == '>' || c == '(' || c == ')')
		return (1);
	return (0);
}
