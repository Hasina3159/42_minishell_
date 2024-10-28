/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_predecence.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazafin <arazafin@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 07:27:00 by arazafin          #+#    #+#             */
/*   Updated: 2024/10/08 07:28:35 by arazafin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	test(t_token *token)
{
	if (token->type == T_IN || token->type == T_OUT
		|| token->type == T_OUT_APPEND || token->type == T_HERE_DOC
		|| token->type == T_HD || token->type == T_FILE_IN
		|| token->type == T_FILE_OUT)
		return (1);
	return (0);
}

int	get_token_precedence(t_token *token)
{
	if (token->type == T_COMMAND)
		return (-1);
	else if (token->type == T_WORD || token->type == T_VAR)
		return (0);
	else if (token->type == T_STRING_S || token->type == T_STRING_D)
		return (1);
	else if (token->type == T_OPERATOR)
		return (2);
	else if (token->type == T_PIPE)
		return (3);
	else if (test(token))
		return (4);
	else if (token->type == T_AND)
		return (5);
	else if (token->type == T_OR)
		return (6);
	else if (token->type == T_P_OPEN || token->type == T_P_CLOSE)
		return (7);
	else if (token->type == T_END)
		return (8);
	else
	{
		printf("Unknown token type: %d\n", token->type);
		return (-1);
	}
}
