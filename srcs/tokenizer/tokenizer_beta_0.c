/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_beta_0.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 15:41:47 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/12/21 13:27:21 by ntodisoa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_set_operator_0(t_token *token)
{
	int	len;

	len = ft_strlen(token->value);
	if (token->type == T_END)
		return ;
	if (token->second_type != T_STRING_S || token->second_type != T_STRING_D)
	{
		if (!ft_strncmp(token->value, "|", len))
			token->type = T_PIPE;
		else if (!ft_strncmp(token->value, "||", len))
			token->type = T_OR;
		else if (!ft_strncmp(token->value, "&&", len))
			token->type = T_AND;
		else if (!ft_strncmp(token->value, "(", len))
			token->type = T_P_OPEN;
	}
}

void	ft_set_operator_1(t_token *token)
{
	int	len;

	len = ft_strlen(token->value);
	if (token->type == T_END)
		return ;
	if (token->second_type != T_STRING_S || token->second_type != T_STRING_D)
	{
		if (!ft_strncmp(token->value, ")", len))
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
}

int	ft_is_t_op(int type)
{
	if (type != T_WORD && type != T_COMMAND && type != T_STRING_S
		&& type != T_STRING_D)
		return (1);
	return (0);
}

void	ft_set_other_cond(t_token *prec, t_token *token, t_all *all, int i)
{
	if (prec && !ft_is_t_op(token->type))
	{
		if (prec->type == T_SPACE)
			prec = &all->tokens[i -2];
		if (prec->type == T_OUT || prec->type == T_OUT_APPEND)
			token->type = T_FILE_OUT;
		else if (prec->type == T_IN)
			token->type = T_FILE_IN;
		else if (prec->type == T_HD)
			token->type = T_HD_ENDER;
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
