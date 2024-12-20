/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:31:40 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/12/20 09:41:29 by ntodisoa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_end_token(t_all *all)
{
	if (all->token_index > 0)
	{
		all->current_token[all->token_index] = 0;
		ft_add_token(all, T_WORD, all->current_token);
	}
	ft_add_token(all, T_END, "");
}

void	ft_create_token(t_all *all)
{
	while (all->i < ft_strlen(all->cmd))
	{
		if (!ft_in_quotes_operation(all))
		{
			if (ft_isspace(all->cmd[all->i]))
			{
				if (all->token_index > 0)
				{
					all->current_token[all->token_index] = 0;
					ft_add_token(all, T_WORD, all->current_token);
					all->token_index = 0;
				}
				ft_add_token(all, T_SPACE, " ");
			}
			else if (!ft_start_quotes(all) && ft_is_operator(all->cmd[all->i]))
				ft_sep_operation(all);
			else
				all->current_token[all->token_index++] = all->cmd[all->i];
		}
		all->i = all->i + 1;
	}
	ft_end_token(all);
}

int	ft_tokenize(t_all *all)
{
	t_token	*tokens;

	ft_init_t_all(all);
	ft_create_token(all);
	ft_set_other(all);
	ft_set_other_1(all);
	ft_set_other_2(all);
	ft_expander(all);
	tokens = ft_create_copy_token(all);
	del_token(all);
	ft_restore_token(all, tokens);
	ft_set_command(all);
	ft_finalize_token(all);
	if (input_error(all))
		return (1);
	all->nb_cmd = count_cmd(all);
	return (0);
}
