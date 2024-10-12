/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazafin <arazafin@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 09:35:20 by arazafin          #+#    #+#             */
/*   Updated: 2024/10/11 21:30:30 by arazafin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_set_operator(t_token *token)
{
	int	len;

	len = ft_strlen(token->value);
	if (len == 0)
	{
		token->type = T_END;
		return ;
	}
	if (!ft_strncmp(token->value, "|", len))
		token->type = T_PIPE;
	else if (!ft_strncmp(token->value, "||", len))
		token->type = T_OR;
	else if (!ft_strncmp(token->value, "&&", len))
		token->type = T_AND;
	else if (!ft_strncmp(token->value, "(", len))
		token->type = T_P_OPEN;
	else if (!ft_strncmp(token->value, ")", len))
		token->type = T_P_CLOSE;
	else if (!ft_strncmp(token->value, "<", len))
		token->type = T_IN;
	else if (!ft_strncmp(token->value, ">", len))
		token->type = T_OUT;
	else if (!ft_strncmp(token->value, ">>", len))
		token->type = T_OUT_APPEND;
	else if (!ft_strncmp(token->value, "<<", len))
		token->type = T_HD;
}

int	ft_is_t_op(int type)
{
	if (type != T_WORD && type != T_COMMAND && type != T_STRING_S
		&& type != T_STRING_D)
		return (1);
	return (0);
}

void	ft_set_command(t_all *all)
{
	int		i;
	t_token	*token;

	i = 0;
	while (i < all->token_count)
	{
		token = &all->tokens[i];
		if ((i == 0 && !ft_is_t_op(token->type))
				|| (i != 0 && i < all->token_count - 1
				&& ft_is_t_op(all->tokens[i - 1].type)
				&& !ft_is_t_op(token->type)))
			token->type = T_COMMAND;
		i++;
	}
}

void	ft_set_other(t_all *all)
{
	int		i;
	t_token	*token;
	t_token	*prec;
	int		len;

	i = 0;
	while (i < all->token_count)
	{
		token = &all->tokens[i];
		len = ft_strlen(token->value);
		if (len == 0)
			break ;
		prec = NULL;
		if (i != 0)
			prec = &all->tokens[i - 1];
		if (prec && !ft_is_t_op(token->type))
		{
			if (!ft_strncmp(prec->value, ">", ft_strlen(prec->value))
				|| !ft_strncmp(prec->value, ">>", ft_strlen(prec->value)))
			{
				token->type = T_FILE_OUT;
				i++;
				continue ;
			}
			else if (!ft_strncmp(prec->value, "<", ft_strlen(prec->value)))
			{
				token->type = T_FILE_IN;
				i++;
				continue ;
			}
			else if (!ft_strncmp(prec->value, "<<", ft_strlen(prec->value)))
			{
				token->type = T_HD_ENDER;
				i++;
				continue ;
			}
		}
		i++;
	}
	i = 0;
	while (i < all->token_count)
	{
		token = &all->tokens[i];
		ft_set_operator(token);
		i++;
	}
}

void	ft_set_other_1(t_all *all)
{
	int		i;
	t_token	*token;

	i = 0;
	while (i < all->token_count)
	{
		token = &all->tokens[i];
		if (token->type == T_STRING_D || token->type == T_STRING_S)
			token->type = T_WORD;
		i++;
	}
}

static int	i_n_op(int type)
{
	if (type == T_PIPE)
		return (1);
	else if (type == T_OR)
		return (1);
	else if (type == T_AND)
		return (1);
	return (0);
}

void	ft_set_other_2(t_all *all)
{
	int		i;
	t_token	*token;

	i = 0;
	while (i < all->token_count)
	{
		token = &all->tokens[i];
		if (i_n_op(token->type))
		{
			if (token->second_type == T_STRING_S || token->second_type == T_STRING_D)
				token->type = T_WORD;
		}
		i++;
	}
}
