/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:31:40 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/12/06 16:58:57 by ntodisoa         ###   ########.fr       */
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
			if (all->tokens[i].value)
			{
				free(all->tokens[i].value);
				all->tokens[i].value = NULL;
			}
			all->tokens[i].value = wildcard;
		}
		i++;
	}
	free(dirs);
}

char	*ft_show_token(t_token *token)
{
	int	len;

	len = ft_strlen(token->value);
	if (len == 0)
		return "END";
	if (!ft_strncmp(token->value, "|", len))
		return "PIPE";
	else if (!ft_strncmp(token->value, "||", len))
		return "OR";
	else if (!ft_strncmp(token->value, "&&", len))
		return "AND";
	else if (!ft_strncmp(token->value, "(", len))
		return "P_OPEN";
	else if (!ft_strncmp(token->value, ")", len))
		return "P_CLOSE";
	else if (!ft_strncmp(token->value, "<", len))
		return "RED_IN";
	else if (!ft_strncmp(token->value, ">", len))
		return "RED_OUT";
	else if (!ft_strncmp(token->value, ">>", len))
		return "RED_APPEND";
	else if (!ft_strncmp(token->value, "<<", len))
		return "HERE_DOC";
	else if (token->type == T_COMMAND)
		return "COMMAND";
	else if (token->type == T_WORD)
		return "ARG";
	else if (token->type == T_STRING_S)
		return "STRING_S";
	else if (token->type == T_STRING_D)
		return "STRING_D";
	else if (token->type == T_FILE_OUT)
		return "FILE_OUT";
	else if (token->type == T_FILE_IN)
		return "FILE_IN";
	else if (token->type == T_HD_ENDER)
		return "T_HD_ENDER";
	else if (token->type == T_SPACE)
		return "T_SPACE";
	else
		return "END";
}

void	ft_print_tokens(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->token_count)
	{
		printf("t_token %d: Value: %s, Type: '%s', ind : %d\n", i,
			all->tokens[i].value, ft_show_token(&all->tokens[i]),
			all->tokens[i].type);
		i++;
	}
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
