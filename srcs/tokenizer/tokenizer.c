/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazafin <arazafin@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 09:18:57 by arazafin          #+#    #+#             */
/*   Updated: 2024/10/12 16:06:57 by arazafin         ###   ########.fr       */
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
					printf("-------------------------------------oooooooooooooooooooo-------------------\n");
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
			free(all->tokens[i].value);
			all->tokens[i].value = wildcard;
		}
		i++;
	}
	free(dirs);
}
// !

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

// !
int	ft_tokenize(t_all *all)
{
	t_token	*tokens;

	ft_init_t_all(all);
	ft_create_token(all);
	ft_set_other(all);
	//ft_show_sanitized_command(all);
	//printf("\n");
	//ft_print_tokens(all);
	//printf("--1 \n");
	ft_set_other_1(all);
	//printf("--2 \n");
	ft_set_other_2(all);
	//printf("--3 \n");
	//ft_show_sanitized_command(all);
	tokens = ft_create_copy_token(all);
	//printf("--4 \n");
	del_token(all);
	//printf("--5 \n");
	ft_restore_token(all, tokens);
	ft_print_tokens(all);
	//ft_show_sanitized_command(all);
	//printf("--6 \n");
	while (!ft_replace_all_vars(all))
		continue ;
	ft_replace_all_wildcards(all);
	ft_expander(all);
	ft_set_command(all);
	ft_finalize_token(all);
	//
	//
	if (input_error(all))
		return (1);
	return (0);
}

//TODO : Creer une copie de t_all, avec les tokens encore vide pour ensuite copier les valeur deja strippE des tokens