/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazafin <arazafin@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 11:11:13 by arazafin          #+#    #+#             */
/*   Updated: 2024/10/26 16:41:02 by arazafin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_expander_exit_status(t_all *all, t_token *token, int i)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	char	*exit_status;

	tmp = ft_substr(token->value, 0, i);
	tmp2 = ft_substr(token->value, i + 2, ft_strlen(token->value) - i - 2);
	exit_status = ft_itoa(all->exit_status);
	tmp3 = ft_strjoin(tmp, exit_status);
	free(token->value);
	token->value = ft_strjoin(tmp3, tmp2);
	free(tmp);
	free(tmp2);
	free(tmp3);
	free(exit_status);
}

int	ft_expander_word(t_all *all, t_token *token)
{
	int	i;

	i = 0;
	while (token->value[i])
	{
		if (token->value[i] == '$' && token->value[i + 1] != '\0')
		{
			if (token->value[i + 1] == '?')
				ft_expander_exit_status(all, token, i);
		}
		i++;
	}
	return (0);
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
			ft_expander_word(all, &all->tokens[i]);
		i++;
	}
	return (0);
}
