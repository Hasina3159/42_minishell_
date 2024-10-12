/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_show_sanitized_command.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazafin <arazafin@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 08:15:38 by arazafin          #+#    #+#             */
/*   Updated: 2024/10/08 08:19:28 by arazafin         ###   ########.fr       */
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
