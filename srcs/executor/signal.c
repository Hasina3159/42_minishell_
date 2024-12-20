/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:28:14 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/12/20 09:40:43 by ntodisoa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	is_second(int *check)
{
	*check = 1;
	close(STDIN_FILENO);
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	ft_sigint(int sig, siginfo_t *info, void *ucontext)
{
	static t_all	*all;
	static int		check = 0;

	(void)info;
	if (!all)
	{
		all = ucontext;
		return ;
	}
	if (all->exit_status != 130)
		check = 0;
	all->exit_status = 128 + sig;
	if (all->second == 1)
		is_second(&check);
	else if (sig == SIGINT)
	{
		if (check == 0)
			printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	setup_signal(int sig, t_state state)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	if (state == DEFAULT || state == IGNORE)
	{
		sa.sa_flags = SA_RESTART;
		if (state == DEFAULT)
			sa.sa_handler = SIG_DFL;
		else if (state == IGNORE)
			sa.sa_handler = SIG_IGN;
	}
	else
	{
		sa.sa_flags = SA_RESTART | SA_SIGINFO;
		if (state == CUSTOM)
			sa.sa_sigaction = ft_sigint;
	}
	if (sigaction(sig, &sa, NULL) != 0)
		perror("sigaction");
}
