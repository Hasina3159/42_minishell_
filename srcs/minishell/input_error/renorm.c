/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renorm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazafin <arazafin@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 07:16:07 by arazafin          #+#    #+#             */
/*   Updated: 2024/10/08 07:19:09 by arazafin         ###   ########.fr       */
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
