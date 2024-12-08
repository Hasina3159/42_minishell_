/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_0.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:31:07 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/12/08 10:56:22 by ntodisoa         ###   ########.fr       */
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
		if (all->token_index > 0)
		{
			all->current_token[all->token_index] = 0;
			ft_add_token(all, T_WORD, all->current_token);
			all->token_index = 0;
		}
		all->in_quotes = 1;
		all->quote_char = all->cmd[all->i];
		all->current_token[all->token_index] = all->quote_char;
		all->i++;
		all->token_index++;
		return (1);
	}
	return (0);
}

int	ft_in_quotes_operation(t_all *all)
{
	char	*tmp;

	if (all->in_quotes)
	{
		if (all->cmd[all->i] == all->quote_char)
		{
			all->current_token[all->token_index++] = all->quote_char;
			all->current_token[all->token_index] = 0;
			if (all->quote_char == '\'')
				tmp = ft_strtrim(all->current_token, "'");
			else
				tmp = ft_strtrim(all->current_token, "\"");
			ft_strlcpy(all->current_token, tmp, ft_strlen(tmp) + 1);
			free(tmp);
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
