/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_show_sanitized_command.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:35:47 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/12/20 09:41:37 by ntodisoa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_show_sanitized_command(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->token_count)
	{
		printf("%s ", all->tokens[i].value);
		i++;
	}
}
