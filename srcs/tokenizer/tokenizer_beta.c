/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_beta.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 15:39:33 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/12/08 15:51:54 by ntodisoa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_set_command(t_all *all)
{
	int		i;
	t_token	*token;

	i = 0;
	while (i < all->token_count)
	{
		token = &all->tokens[i];
		if ((i == 0 && !ft_is_t_op(token->type)) \
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
		ft_set_operator(token);
		i++;
	}
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
		ft_set_other_cond(prec, token, all, i);
		i++;
	}
}

t_token	*ft_create_copy_token(t_all *all)
{
	int				i;
	int				j;
	static t_token	tokens[TOKENS_MAX];

	i = 0;
	j = 0;
	ft_copy_token(&all->tokens[0], &tokens[0]);
	ft_create_copy_token_0(tokens, all, i, j);
	i = 0;
	while (tokens[i].type != T_END)
		i++;
	all->token_count = i + 1;
	return (tokens);
}

void	ft_restore_token(t_all *all, t_token *tokens)
{
	int	i;

	i = 0;
	while (i < all->token_count)
	{
		all->tokens[i].type = tokens[i].type;
		all->tokens[i].second_type = tokens[i].second_type;
		all->tokens[i].value = tokens[i].value;
		i++;
	}
}

void	ft_set_operator(t_token *token)
{
	ft_set_operator_0(token);
	ft_set_operator_1(token);
}
