/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:22:55 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/12/08 10:58:09 by ntodisoa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	del_token(t_all *all)
{
	int	i;

	i = 0;
	while (i < TOKENS_MAX)
	{
		if (all->tokens[i].value)
		{
			free(all->tokens[i].value);
			all->tokens[i].value = NULL;
		}
		i++;
	}
}

void	clean_all(t_all *all, char **cmd)
{
	del_token(all);
	free(all->cmd);
	free_split(cmd);
	if (!all->sh)
		del_env(&all->env);
}

int	free_all(t_all *all)
{
	del_token(all);
	free(all->cmd);
	del_env(&all->env);
	rl_clear_history();
	if (!all->sh)
	{
		close(all->fd[0]);
		close(all->fd[1]);
		if (all->tmp > 0)
			close(all->tmp);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
	}
	return (0);
}

int	check_exit_arg(char *arg, t_all *all, char **cmd)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (i == 0)
		{
			if (arg[0] == '+' || arg[0] == '-')
				i++;
		}
		if (ft_isdigit((int)arg[i]) == 0)
		{
			print_error("exit", arg, "numeric argument required");
			free_split(cmd);
			free_all(all);
			exit(2);
		}
		i++;
	}
	return (0);
}

int	ft_exit(t_all *all, char **argv)
{
	int	argc;
	int	exit_s;

	argc = ft_count_splitted(argv);
	if (!all->sh)
		printf("exit\n");
	if (argc == 1)
	{
		free_split(argv);
		free_all(all);
		exit(all->exit_status);
	}
	check_exit_arg(argv[1], all, argv);
	if (argc == 2)
	{
		exit_s = ft_atoi(argv[1]);
		free_all(all);
		free_split(argv);
		exit (exit_s);
	}
	print_error("exit", NULL, "too much arguments");
	return (1);
}
