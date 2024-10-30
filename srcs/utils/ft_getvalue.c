/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getvalue.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazafin <arazafin@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 08:14:18 by arazafin          #+#    #+#             */
/*   Updated: 2024/10/29 20:03:16 by arazafin         ###   ########.fr       */
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
