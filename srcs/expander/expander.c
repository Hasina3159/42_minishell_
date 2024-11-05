/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazafin <arazafin@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 11:11:13 by arazafin          #+#    #+#             */
/*   Updated: 2024/11/05 10:31:52 by arazafin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	expand_token(t_all *all, t_token *token, int i)
{
	char	*expanded;

	expanded = expand_variables(all, token->value, i);
	if (expanded)
	{
		free(token->value);
		token->value = expanded;
	}
}

int	ft_expander(t_all *all)
{
	int		i;

	i = 0;
	while (all->tokens[i].type != T_END)
	{
		if (all->tokens[i].type != T_STRING_S
			&& all->tokens[i].second_type != T_STRING_S
			&& all->tokens[i].type != T_HD_ENDER
			&& all->tokens[i].second_type != T_HD_ENDER)
			expand_token(all, &all->tokens[i], i);
		i++;
	}
	return (0);
}
