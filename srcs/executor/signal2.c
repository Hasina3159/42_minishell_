/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:28:22 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/12/20 09:40:44 by ntodisoa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
