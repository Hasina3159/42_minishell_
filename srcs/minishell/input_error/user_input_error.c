/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazafin <arazafin@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 14:37:07 by arazafin          #+#    #+#             */
/*   Updated: 2024/10/08 07:10:30 by arazafin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	test_t_pipe(t_token *tokens, int i)
{
	int	type;

	type = tokens[i + 1].type;
	if (type == T_AND)
	{
		print_error(NULL, NULL, "syntax error near unexpected token « |& »");
		return (1);
	}
	else if (type != T_WORD && type != T_COMMAND)
	{
		print_error(NULL, NULL, "syntax error near unexpected token « | »");
		return (1);
	}
	else if (i == 0)
	{
		print_error(NULL, NULL, "syntax error near unexpected token « | »");
		return (1);
	}
	return (0);
}

int	test_t_or(t_token *tokens, int i)
{
	if (tokens[i + 1].type != T_WORD && tokens[i + 1].type != T_COMMAND)
	{
		print_error(NULL, NULL, "syntax error near unexpected token « || »");
		return (1);
	}
	else if (i == 0)
	{
		print_error(NULL, NULL, "syntax error near unexpected token « || »");
		return (1);
	}
	return (0);
}

int	test_and(t_token *tokens, int i)
{
	if (tokens[i + 1].type != T_WORD && tokens[i + 1].type != T_COMMAND)
	{
		print_error(NULL, NULL, "syntax error near unexpected token « && »");
		return (1);
	}
	else if (i == 0)
	{
		print_error(NULL, NULL, "syntax error near unexpected token « && »");
		return (1);
	}
	return (0);
}

int	input_error(t_all *all)
{
	int	i;
	int	error;

	i = -1;
	error = 0;
	while (all->tokens[++i].type != T_END)
	{
		if (all->tokens[i].type == T_HD || all->tokens[i].type == T_IN)
			error = test_hd_in(all->tokens, i);
		else if (all->tokens[i].type == T_OUT
			|| all->tokens[i].type == T_OUT_APPEND)
			error = test_out_n_append(all->tokens, i);
		else if (all->tokens[i].type == T_PIPE)
			error = test_t_pipe(all->tokens, i);
		else if (all->tokens[i].type == T_OR)
			error = test_t_or(all->tokens, i);
		else if (all->tokens[i].type == T_AND)
			error = test_and(all->tokens, i);
		if (error)
		{
			all->exit_status = 2;
			return (2);
		}
	}
	return (0);
}
