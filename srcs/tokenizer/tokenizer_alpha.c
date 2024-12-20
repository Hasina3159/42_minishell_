/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_alpha.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 15:09:00 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/12/20 11:32:28 by ntodisoa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_trim_and_copy(char *current_token, char quote_char)
{
	char	*tmp;

	if (quote_char == '\'')
		tmp = ft_strtrim(current_token, "'");
	else
		tmp = ft_strtrim(current_token, "\"");
	ft_strlcpy(current_token, tmp, ft_strlen(tmp) + 1);
	free(tmp);
}

int	ft_in_quotes_operation(t_all *all)
{
	if (all->in_quotes)
	{
		if (all->cmd[all->i] == all->quote_char)
		{
			all->current_token[all->token_index++] = all->quote_char;
			all->current_token[all->token_index] = 0;
			ft_trim_and_copy(all->current_token, all->quote_char);
			if (all->quote_char == '\'')
				ft_add_token(all, T_STRING_S, all->current_token);
			else
				ft_add_token(all, T_STRING_D, all->current_token);
			all->token_index = 0;
			all->in_quotes = 0;
		}
		else
			all->current_token[all->token_index++] = all->cmd[all->i];
		return (1);
	}
	return (0);
}

void	ft_sep_operation(t_all *all)
{
	if (all->token_index > 0)
	{
		all->current_token[all->token_index] = 0;
		ft_add_token(all, T_WORD, all->current_token);
		all->token_index = 0;
	}
	all->current_token[all->token_index++] = all->cmd[all->i];
	if (all->cmd[all->i + 1] && ft_is_sep(all->cmd[all->i]) && all->cmd[all->i
			+ 1] == all->cmd[all->i])
	{
		all->i = all->i + 1;
		all->current_token[all->token_index++] = all->cmd[all->i];
	}
	all->current_token[all->token_index] = 0;
	ft_add_token(all, T_OPERATOR, all->current_token);
	all->token_index = 0;
}
