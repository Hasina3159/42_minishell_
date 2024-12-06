/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:23:45 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/12/06 15:09:03 by ntodisoa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_cmd_len(t_all *all, int i)
{
	int	j;
	int	len;

	j = i;
	len = 0;
	while (!is_n_op(all->tokens[j].type))
	{
		if (all->tokens[j].type == T_COMMAND || all->tokens[j].type == T_WORD)
		{
			if (ft_strlen(all->tokens[j].value) < 1)
			{
				j++;
				continue ;
			}
			len++;
		}
		j++;
	}
	return (len);
}

char	**ft_tokens_to_char(t_all *all, int *i)
{
	char	**token_str;
	int		len;
	int		j;

	len = get_cmd_len(all, *i);
	if (!len)
		return (NULL);
	token_str = (char **)ft_calloc(len + 1, sizeof(char *));
	if (token_str == NULL)
		return (NULL);
	j = 0;
	while (!is_n_op(all->tokens[*i].type))
	{
		if (all->tokens[*i].type == T_COMMAND || all->tokens[*i].type == T_WORD)
		{
			if (ft_strlen(all->tokens[*i].value) < 1)
			{
				*i = *i + 1;
				continue ;
			}
			token_str[j] = ft_strdup(all->tokens[*i].value);
			j++;
		}
		*i = *i + 1;
	}
	return (token_str);
}

int	is_built(char **av)
{
	if (!ft_strncmp(av[0], "echo", 5))
		return (1);
	else if (!ft_strncmp(av[0], "pwd", 4))
		return (2);
	else if (!ft_strncmp(av[0], "env", 4))
		return (3);
	else if (!ft_strncmp(av[0], "cd", 3))
		return (4);
	else if (!ft_strncmp(av[0], "export", 7))
		return (5);
	else if (!ft_strncmp(av[0], "unset", 6))
		return (6);
	else if (!ft_strncmp(av[0], "exit", 5))
		return (7);
	return (0);
}

int	use_built(t_all *all, int ch, char **cmd)
{
	int	ac;

	if (all->sh == 0)
	{
		close(all->fd[0]);
		close(all->fd[1]);
		all->child_pid = -2;
	}
	ac = ft_count_splitted(cmd);
	if (ch == 1)
		return (ft_echo(ac, cmd, all));
	else if (ch == 2)
		return (ft_pwd(all));
	else if (ch == 3)
		return (ft_env(all));
	else if (ch == 4)
		return (ft_cd(cmd, all));
	else if (ch == 5)
		return (ft_export(all, cmd));
	else if (ch == 6)
		return (ft_unset(all, cmd));
	else if (ch == 7)
		return (ft_exit(all, cmd));
	return (126);
}

void	parent_process(t_all *all)
{
	if (all->has_pipe)
	{
		if (all->tmp != -1)
		{
			close(all->tmp);
			all->tmp = -1;
		}
		all->tmp = all->fd[0];
	}
	else
	{
		if (all->tmp != -1)
			close(all->tmp);
		close(all->fd[0]);
		all->tmp = -1;
	}
	close(all->fd[1]);
}
