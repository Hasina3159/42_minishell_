/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:31:32 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/12/06 10:31:33 by ntodisoa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_hd_lim(t_token *token, int i)
{
	if (i > 0)
	{
		if (token[i - 1].type == T_HD)
			return (1);
	}
	return (0);
}

static void	free_vars(char **vars)
{
	int	i;

	i = 0;
	while (vars[i])
	{
		if (vars[i])
			free(vars[i]);
		i++;
	}
	if (vars)
		free(vars);
}

int	ft_replace_var(t_all *all, t_token *token)
{
	char	**vars;
	char	*value;
	int		i;
	char	*tmp;

	vars = ft_get_all_var(token->value);
	if (vars == NULL)
		return (0);
	i = 0;
	while (vars[i])
	{
		value = ft_getvarvalue(all, &vars[i][1]);
		tmp = ft_strdup(token->value);
		free(token->value);
		token->value = ft_str_repl_copy(tmp, vars[i], value);
		free(tmp);
		if (token->value)
		{
			free_vars(vars);
			return (0);
		}
		i++;
	}
	free_vars(vars);
	return (1);
}

int	ft_replace_all_vars(t_all *all)
{
	t_token	*token;
	int		i;

	i = 0;
	token = all->tokens;
	while (i < all->token_count)
	{
		if (!is_hd_lim(token, i)
			&& (token[i].type != T_STRING_S
				&& token[i].second_type != T_STRING_S)
			&& !ft_replace_var(all, &token[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_finalize_token(t_all *all)
{
	t_token	*tokens;
	t_token	*now;
	t_token	*prec;
	int		i;

	i = 0;
	tokens = all->tokens;
	while (i < all->token_count)
	{
		if (i != 0)
			prec = &tokens[i - 1];
		else
			prec = NULL;
		now = &tokens[i];
		if (prec && (prec->type == T_FILE_OUT || prec->type == T_FILE_IN)
			&& now->type == T_WORD)
			now->type = T_COMMAND;
		i++;
	}
}
