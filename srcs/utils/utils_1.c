/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 15:58:31 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/12/08 16:01:43 by ntodisoa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_is_separator(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

int	ft_is_quotes(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}

void	ft_pass_separator(char const *s, int *i, int *count, int *is_in_a_str)
{
	while (s[*i] && (ft_is_separator(s[*i]) || s[*i] == ' ')
		&& !ft_is_quotes(s[*i]) && !*is_in_a_str)
	{
		if (ft_is_separator(s[*i]))
			*count = *count + 1;
		*i = *i + 1;
	}
}
