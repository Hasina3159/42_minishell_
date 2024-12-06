/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getvalue.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:33:40 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/12/06 10:33:41 by ntodisoa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_getvarvalue(t_all *all, char *var)
{
	t_env	*tmp;

	tmp = all->env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, var, ft_strlen(var) + 1))
			return (tmp->value);
		tmp = tmp->next;
	}
	if (tmp)
		return (tmp->value);
	return ("");
}

char	*ft_is_in_env(t_all *all, char *var)
{
	t_env	*tmp;

	tmp = all->env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, var, ft_strlen(var) + 1))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}
