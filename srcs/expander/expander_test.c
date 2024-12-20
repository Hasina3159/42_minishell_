/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:28:43 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/12/20 09:40:47 by ntodisoa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*expand_variables(t_all *all, char *str, int i)
{
	t_expand	exp;

	if (!str)
		return (NULL);
	exp.result = ft_strdup("");
	exp.i = 0;
	exp.tok_i = i;
	while (str[exp.i])
	{
		if (str[exp.i] == '$')
			handle_dollar(all, str, &exp);
		else
			append_char3(&exp.result, str[exp.i]);
		if (!str[exp.i])
			break ;
		exp.i++;
	}
	return (exp.result);
}
