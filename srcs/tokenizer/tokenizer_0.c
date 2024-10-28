/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_0.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazafin <arazafin@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 09:26:57 by arazafin          #+#    #+#             */
/*   Updated: 2024/10/11 10:08:39 by arazafin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
/**
 *\brief initialise t_all
 *\param *all: un pointeur de type t_all
 *\return rien
 */
void	ft_init_t_all(t_all *all)
{
	all->i = 0;
	all->in_quotes = 0;
	all->token_index = 0;
	all->quote_char = 0;
	all->token_count = 0;
}

int	ft_is_operator_type(int type)
{
	if (type != T_STRING_D && type != T_STRING_S && type != T_WORD)
		return (1);
	return (0);
}

void	ft_add_token(t_all *all, int type, char *value)
{
	//printf("1 - [%s], [%d]\n", all->tokens[all->token_count].value, all->token_count);
	if (all->token_count > 0 && !ft_is_operator_type(all->tokens[all->token_count - 1].type))
	{
		//printf("val : %s", all->tokens[all->token_count - 1].value);
		//printf("content : %s\n", ft_strjoin(all->tokens[all->token_count - 1].value, value));
		//return;
	}
	all->tokens[all->token_count].type = type;
	all->tokens[all->token_count].second_type = type;
	all->tokens[all->token_count].value = ft_strdup(value);
	all->token_count = all->token_count + 1;
	//printf("2 - [%s], [%d], [%d]\n", all->tokens[all->token_count - 1].value, all->tokens[all->token_count].type, all->token_count);

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
		all->i++;
		return (1);
	}
	return (0);
}

int	ft_in_quotes_operation(t_all *all)
{
	if (all->in_quotes)
	{
		if (all->cmd[all->i] == all->quote_char)
		{
			//all->current_token[all->token_index++] = all->cmd[all->i];
			all->current_token[all->token_index++] = 0;
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
