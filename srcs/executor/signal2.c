/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazafin <arazafin@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:38:45 by arazafin          #+#    #+#             */
/*   Updated: 2024/10/25 11:45:39 by arazafin         ###   ########.fr       */
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
