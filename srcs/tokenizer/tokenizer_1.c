/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:31:17 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/12/20 14:49:36 by ntodisoa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
			if (token->second_type == T_STRING_S || \
			token->second_type == T_STRING_D)
				token->type = T_WORD;
		}
		i++;
	}
}

void	ft_copy_token(t_token *src, t_token *dst)
{
	char	*tmp;

	dst->second_type = src->second_type;
	dst->type = src->type;
	tmp = ft_strdup(src->value);
	dst->value = tmp;
}

int	ft_create_copy_cond(t_token *next_token, int *i)
{
	if (next_token->type == T_SPACE)
	{
		*i = *i + 1;
		return (1);
	}
	return (0);
}

void	ft_create_copy_token_0(t_token	*tokens, t_all *all, int i, int j)
{
	t_token	*next_token;
	t_token	*token;
	char	*tmp;

	while (i < all->token_count - 1)
	{
		token = &all->tokens[i];
		next_token = &all->tokens[i + 1];
		if (ft_create_copy_cond(next_token, &i))
			continue ;
		else if (token->type == T_WORD && next_token->type == T_WORD)
		{
			tmp = tokens[j].value;
			tokens[j].value = ft_strjoin(tokens[j].value, next_token->value);
			free(tmp);
		}
		else
		{
			j++;
			ft_copy_token(next_token, &tokens[j]);
		}
		i++;
	}
}
