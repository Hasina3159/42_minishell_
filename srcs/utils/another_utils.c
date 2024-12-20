/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   another_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 09:55:30 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/12/20 12:28:28 by ntodisoa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	another_condition(char *value, char **key, t_env **tmp)
{
	if (value && ft_strlen(value) != 0)
	{
		free(*key);
		free((*tmp)->value);
		(*tmp)->value = value;
		return (0);
	}
	return (1);
}
