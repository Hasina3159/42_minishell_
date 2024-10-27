/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazafin <arazafin@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 09:18:57 by arazafin          #+#    #+#             */
/*   Updated: 2024/10/26 16:59:27 by arazafin         ###   ########.fr       */
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

void	ft_replace_all_wildcards(t_all *all)
{
	char	*wildcard;
	t_dir	**dirs;
	int		i;

	i = 0;
	dirs = ft_init_dirs();
	while (i < all->token_count)
	{
		if (ft_count_char(all->tokens[i].value, '*')
			&& all->tokens[i].type != T_STRING_S)
		{
			ft_copy_dir(dirs, ft_strlen(getcwd(NULL, 0)) + 1);
			wildcard = ft_get_wildcard(dirs, all->tokens[i].value);
			free(all->tokens[i].value);
			all->tokens[i].value = wildcard;
		}
		i++;
	}
	free(dirs);
}

int	ft_tokenize(t_all *all)
{
	ft_init_t_all(all);
	ft_create_token(all);
	ft_set_other(all);
	ft_set_other_1(all);
	while (!ft_replace_all_vars(all))
		continue ;
	// ft_replace_all_wildcards(all);
	ft_expander(all);
	ft_set_command(all);
	ft_finalize_token(all);
	if (input_error(all))
		return (1);
	return (0);
}
