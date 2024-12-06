/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renorm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:28:57 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/12/06 10:28:58 by ntodisoa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	in_test(t_token *tokens, int i)
{
	if (ft_strncmp(tokens[i + 1].value, "&&", 2))
	{
		print_error(NULL, NULL,
			"syntax error near unexpected token « && »");
		return (1);
	}
	return (0);
}
