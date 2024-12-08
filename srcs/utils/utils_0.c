/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:36:56 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/12/08 16:00:05 by ntodisoa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_pass_first_cond(char const *s, int *i, int *is_in_a_str)
{
	if (s[*i] && ft_is_quotes(s[*i]))
	{
		if (*is_in_a_str)
			*is_in_a_str = 0;
		else
			*is_in_a_str = s[*i];
		*i = *i + 1;
	}
}

void	ft_pass_second_cond(int is_count_inc, int flag, int *count)
{
	if (!is_count_inc && flag == 1)
		*count = *count + 1;
}

void	ft_pass_quotes(char const *s, int *i, int *count, int *is_in_a_str)
{
	int	flag;
	int	is_count_inc;

	flag = 0;
	is_count_inc = 0;
	ft_pass_first_cond(s, i, is_in_a_str);
	if (*is_in_a_str)
	{
		while (*is_in_a_str)
		{
			flag = 1;
			if (s[*i] && s[*i] == *is_in_a_str)
			{
				*is_in_a_str = 0;
				*i = *i + 1;
				if (*count == 0)
				{
					is_count_inc = 1;
					*count = *count + 1;
				}
			}
			*i = *i + 1;
		}
	}
	ft_pass_second_cond(is_count_inc, flag, count);
}

int	ft_count_words(char const *s)
{
	int	i;
	int	count;
	int	is_in_a_str;
	int	inc_count;

	i = 0;
	count = 0;
	is_in_a_str = 0;
	while (s[i])
	{
		ft_pass_separator(s, &i, &count, &is_in_a_str);
		ft_pass_quotes(s, &i, &count, &is_in_a_str);
		inc_count = 0;
		while (s[i] && !ft_is_separator(s[i]) && s[i] != ' '
			&& !ft_is_quotes(s[i]) && !is_in_a_str)
		{
			inc_count = 1;
			i++;
			printf("-");
		}
		if (inc_count)
			count++;
	}
	return (count);
}
