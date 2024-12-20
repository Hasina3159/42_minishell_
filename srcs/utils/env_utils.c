/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:32:37 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/12/20 09:41:31 by ntodisoa         ###   ########.fr       */
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
		if (!ft_strncmp(tmp->key, key, ft_strlen(key) + 1))
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

void	update_underscore(t_all *all)
{
	char	*key;
	char	*value;
	int		i;

	i = all->token_count - 1;
	key = ft_strdup("_");
	value = NULL;
	while (i >= 0)
	{
		if (all->tokens[i].type == T_WORD || all->tokens[i].type == T_COMMAND)
		{
			if (all->tokens[i].value != NULL && \
			ft_strlen(all->tokens[i].value) > 0)
			{
				value = ft_strdup(all->tokens[i].value);
				break ;
			}
		}
		i--;
	}
	ft_setvarvalue(all, key, value);
}
