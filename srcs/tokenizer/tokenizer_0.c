/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_0.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:31:07 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/12/20 11:32:48 by ntodisoa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_clean_current_token(t_all *all)
{
	size_t	i;

	i = 0;
	while (i < CMD_MAX)
	{
		all->current_token[i] = 0;
		i++;
	}
}

void	ft_clean_current_token_quotes(t_all *all)
{
	size_t	i;
	size_t	quote_nb;

	i = 0;
	quote_nb = 0;
	while (all->in_quotes && i < CMD_MAX)
	{
		if (all->current_token[i] == all->quote_char)
			quote_nb++;
		if (quote_nb >= 1)
			all->current_token[i] = 0;
		i++;
	}
}

void	ft_init_t_all(t_all *all)
{
	all->i = 0;
	all->in_quotes = 0;
	all->token_index = 0;
	all->quote_char = 0;
	all->token_count = 0;
	ft_clean_current_token(all);
}

void	ft_add_token(t_all *all, int type, char *value)
{
	all->tokens[all->token_count].type = type;
	all->tokens[all->token_count].second_type = type;
	all->tokens[all->token_count].value = ft_strdup(value);
	all->token_count = all->token_count + 1;
	ft_clean_current_token(all);
}

int	ft_start_quotes(t_all *all)
{
	if (all->cmd[all->i] == '\'' || all->cmd[all->i] == '\"')
	{
		all->in_quotes = 1;
		if (all->token_index > 0)
		{
			all->current_token[all->token_index] = 0;
			ft_add_token(all, T_WORD, all->current_token);
			all->token_index = 0;
		}
		all->quote_char = all->cmd[all->i];
		all->current_token[all->token_index] = all->quote_char;
		all->i++;
		all->token_index++;
		return (1);
	}
	return (0);
}
