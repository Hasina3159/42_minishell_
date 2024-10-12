/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_splitted.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazafin <arazafin@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 08:13:20 by arazafin          #+#    #+#             */
/*   Updated: 2024/10/08 08:49:32 by arazafin         ###   ########.fr       */
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
