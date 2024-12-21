/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_alpha.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 15:09:00 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/12/21 14:28:28 by ntodisoa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


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
		printf("t_token [%d]: Value: [%s], Type: [%s], ind : [%d]\n", i,
			all->tokens[i].value, ft_show_token(&all->tokens[i]),
			all->tokens[i].type);
		i++;
	}
}

int	ft_finalize(t_all *all)
{
	if (!ft_strncmp(all->current_token, "\"\"", 2) && \
	all->quote_char == '"')
	{
		ft_strlcpy(all->current_token, "", 1);
		ft_add_token(all, T_STRING_D, "");		
		return (1);
	}
	else if (!ft_strncmp(all->current_token, "''", 2) && \
	all->quote_char == '\'')
	{
		ft_strlcpy(all->current_token, "", 1);
		ft_add_token(all, T_STRING_S, "");
		return (1);
	}
	return (0);
};

void	ft_trim_and_copy(char *current_token, char quote_char)
{
	char	*tmp;

	if (quote_char == '\'')
		tmp = ft_strtrim(current_token, "'");
	else
		tmp = ft_strtrim(current_token, "\"");
	ft_strlcpy(current_token, tmp, ft_strlen(tmp) + 1);
	free(tmp);
}

int	ft_in_quotes_operation(t_all *all)
{
	ft_print_tokens(all);
	//printf("all->current_token : [%s] [%d] [%ld] [%c]\n", all->current_token, all->token_index, all->i, all->cmd[all->i]);
	if (all->in_quotes)
	{
		printf("\t\t---> 0 - all->current_token : [%s], [%c]\n", all->current_token, all->cmd[all->i]);
		if (all->cmd[all->i] == all->quote_char)
		{
			all->current_token[all->token_index++] = all->quote_char;
			all->current_token[all->token_index] = 0;
			printf("\t\t---> 1 - all->current_token : [%s]\n", all->current_token);
			ft_trim_and_copy(all->current_token, all->quote_char);
			//printf("2 - all->current_token : [%s]\n", all->current_token);
			if (all->quote_char == '\'')
				ft_add_token(all, T_STRING_S, all->current_token);
			else
				ft_add_token(all, T_STRING_D, all->current_token);
			all->token_index = 0;
			all->in_quotes = 0;
		}
		else
			all->current_token[all->token_index++] = all->cmd[all->i];

		return (1);
	}
	return (0);
}

void	ft_sep_operation(t_all *all)
{
	if (all->token_index > 0)
	{
		all->current_token[all->token_index] = 0;
		ft_add_token(all, T_WORD, all->current_token);
		all->token_index = 0;
	}
	all->current_token[all->token_index++] = all->cmd[all->i];
	if (all->cmd[all->i + 1] && ft_is_sep(all->cmd[all->i]) && all->cmd[all->i
			+ 1] == all->cmd[all->i])
	{
		all->i = all->i + 1;
		all->current_token[all->token_index++] = all->cmd[all->i];
	}
	all->current_token[all->token_index] = 0;
	ft_add_token(all, T_OPERATOR, all->current_token);
	all->token_index = 0;
}
