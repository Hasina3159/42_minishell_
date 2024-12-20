/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_splitted.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:33:28 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/12/20 09:41:33 by ntodisoa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_count_splitted(char **splitted)
{
	int	i;

	if (!splitted)
		return (0);
	i = 0;
	while (splitted[i])
		i++;
	return (i);
}
