/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_wildcards.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:33:33 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/12/20 09:41:33 by ntodisoa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_count_wildcards(char *w)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (w[i])
	{
		if (w[i] == '*')
		{
			while (w[i] && w[i] == '*')
				i++;
			count++;
		}
		i++;
	}
	return (count);
}
