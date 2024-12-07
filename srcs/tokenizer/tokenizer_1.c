/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:31:17 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/12/07 13:34:22 by ntodisoa         ###   ########.fr       */
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
	if (token->second_type != T_STRING_S || token->second_type != T_STRING_D)
	{
		if (!ft_strncmp(token->value, "|", len) )
			token->type = T_PIPE;
		else if (!ft_strncmp(token->value, "||", len) )
			token->type = T_OR;
		else if (!ft_strncmp(token->value, "&&", len) )
			token->type = T_AND;
		else if (!ft_strncmp(token->value, "(", len) )
			token->type = T_P_OPEN;
		else if (!ft_strncmp(token->value, ")", len) )
			token->type = T_P_CLOSE;
		else if (!ft_strncmp(token->value, "<", len) )
			token->type = T_IN;
		else if (!ft_strncmp(token->value, ">", len) )
			token->type = T_OUT;
		else if (!ft_strncmp(token->value, ">>", len) )
			token->type = T_OUT_APPEND;
		else if (!ft_strncmp(token->value, "<<", len) )
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
// TODO: si T_SPACE est entre les token T_FILE_IN, T_FILE_OUT et T_HD_ENDER ne sont pas definie
// FIXME: io le probleme satria miankina amin'io le input_error
// FIXME: test futsn ty fa mila verifiena iany lou fa otrzao de ts manao input_error
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

void ft_copy_token(t_token *src, t_token *dst)
{
	char	*tmp;
	dst->second_type = src->second_type;
	dst->type = src->type;
	tmp = ft_strdup(src->value);
	printf("--> VALUE : [%s : %lu], [%p]\n", tmp, sizeof(char) * ft_strlen(tmp), tmp);
	dst->value = tmp;
}


t_token *ft_create_copy_token(t_all *all)
{
	int		i;
	int		j;
	static t_token	tokens[TOKENS_MAX];
	t_token	*token;
	t_token	*next_token;

	i = 0;
	j = 0;
	ft_copy_token(&all->tokens[0], &tokens[0]);
	while (i < all->token_count - 1)
	{
		token = &all->tokens[i];
		next_token = &all->tokens[i + 1];
		if (next_token->type == T_SPACE)
		{
			i++;
			continue;
		}
		else if (token->type == T_WORD && next_token->type == T_WORD)
			tokens[j].value = ft_strjoin(tokens[j].value, next_token->value);
		else
		{
			j++;
			ft_copy_token(next_token, &tokens[j]);
		}
		i++;
	}
	i = 0;
	while (tokens[i].type != T_END)
		i++;
	all->token_count = i + 1;
	return (tokens);
}

void ft_restore_token(t_all *all, t_token *tokens)
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
