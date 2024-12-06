/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:23:16 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/12/06 10:23:17 by ntodisoa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	del_node(t_env *node, void (*del)(void *))
{
	del(node->key);
	del(node->value);
	del(node);
}

void	del_from_env(char *var, t_env **env)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = *env;
	prev = NULL;
	while (tmp)
	{
		if (!ft_strncmp(var, tmp->key, ft_strlen(var) + 1))
		{
			if (prev == NULL)
				*env = tmp->next;
			else
				prev->next = tmp->next;
			del_node(tmp, free);
			break ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

int	ft_unset(t_all *all, char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (is_valid_arg(av[i]))
			del_from_env(av[i], &all->env);
		else
			print_error(av[0], av[i], "is not a valid identifier");
		i++;
	}
	// if (all->nb_cmd == 1)
	// 	update_underscore(all);
	return (SUCCESS);
}
