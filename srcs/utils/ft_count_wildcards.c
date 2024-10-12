/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_wildcards.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazafin <arazafin@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 08:14:03 by arazafin          #+#    #+#             */
/*   Updated: 2024/10/08 08:49:54 by arazafin         ###   ########.fr       */
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
