/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazafin <arazafin@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 07:32:46 by arazafin          #+#    #+#             */
/*   Updated: 2024/10/21 07:58:06 by arazafin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_sigint(int sig, siginfo_t *info, void *ucontext)
{
	static t_all	*all;

	(void)info;
	if (!all)
	{
		all = ucontext;
		return ;
	}
	all->exit_status = 128 + sig;
	if (sig == SIGINT)
	{
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

void	reset_parent_sig(void)
{
	setup_signal(SIGINT, CUSTOM);
	setup_signal(SIGQUIT, IGNORE);
}

void	setup_parent_signals(void)
{
	setup_signal(SIGINT, IGNORE);
	setup_signal(SIGQUIT, IGNORE);
}

void	setup_child_signals(void)
{
	setup_signal(SIGINT, DEFAULT);
	setup_signal(SIGQUIT, DEFAULT);
}
