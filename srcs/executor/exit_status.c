/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazafin <arazafin@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 18:22:50 by arazafin          #+#    #+#             */
/*   Updated: 2024/10/21 09:45:13 by arazafin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_sig(int sig, int *print)
{
	if (*print == 0)
	{
		if (sig == SIGINT)
			printf("\n");
		else if (sig == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", 2);
		*print = 1;
	}
}

void	get_exit_status(t_all *all)
{
	pid_t	wpid;
	int		sig;
	int		last_status;
	int		print;

	wpid = 1;
	last_status = 0;
	print = 0;
	while (wpid > 0)
	{
		wpid = waitpid(-1, &all->statloc, 0);
		if (wpid == -1)
			break ;
		if (WIFEXITED(all->statloc))
			last_status = WEXITSTATUS(all->statloc);
		else if (WIFSIGNALED(all->statloc))
		{
			sig = WTERMSIG(all->statloc);
			print_sig(sig, &print);
			last_status = 128 + sig;
		}
		if (wpid == all->child_pid)
			all->exit_status = last_status;
	}
	reset_parent_sig();
}
