/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazafin <arazafin@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 08:11:47 by arazafin          #+#    #+#             */
/*   Updated: 2024/10/08 08:11:48 by arazafin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_search_key(char *key, t_all *all)
{
	t_env	*tmp;

	tmp = all->env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, key, ft_strlen(tmp->key)))
		{
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

char	*ft_get_env(char *key, t_all *all)
{
	char	*value;
	t_env	*tmp;

	value = NULL;
	tmp = all->env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, key, ft_strlen(tmp->key)))
		{
			value = tmp->value;
			break ;
		}
		tmp = tmp->next;
	}
	return (value);
}

t_env	*ft_create_env(char *key, char *value)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

int	ft_setvarvalue(t_all *all, char *key, char *value)
{
	t_env	*tmp;
	t_env	*last;

	tmp = all->env;
	if (tmp == NULL)
	{
		all->env = ft_create_env(key, value);
		return (0);
	}
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, key, ft_strlen(key)))
		{
			free(key);
			free(tmp->value);
			tmp->value = value;
			return (0);
		}
		if (tmp->next == NULL)
			last = tmp;
		tmp = tmp->next;
	}
	last->next = ft_create_env(key, value);
	return (1);
}
