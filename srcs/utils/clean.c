/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:32:17 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/12/06 15:03:03 by ntodisoa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_split(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != NULL)
	{
		if (cmd[i])
		{
			free(cmd[i]);
			cmd[i] = NULL;
		}
		i++;
	}
	free(cmd);
}

void	del_env(t_env **env)
{
	t_env	*tmp;
	t_env	*next;

	tmp = *env;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->key)
		{
			free(tmp->key);
			tmp->key = NULL;	
		}
		if (tmp->value)
		{
			free(tmp->value);
			tmp->value = NULL;
		}
		if (tmp)
		{
			free(tmp);
			tmp = NULL;
		}
		tmp = next;
	}
	*env = NULL;
}

int	clean_child_b(t_all *all, char **token_str)
{
	free_split(token_str);
	free_all(all);
	return (0);
}

int	clean_child(t_all *all)
{
	del_token(all);
	free(all->cmd);
	rl_clear_history();
	del_env(&all->env);
	return (0);
}
