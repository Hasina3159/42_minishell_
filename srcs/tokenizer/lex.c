/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazafin <arazafin@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 19:59:21 by arazafin          #+#    #+#             */
/*   Updated: 2024/10/21 11:29:07 by arazafin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_first(char *input)
{
	int	i;

	i = 0;
	while (ft_isspace(input[i]))
		i++;
	if (input[i] == '|' || input[i] == '&')
		return (0);
	return (1);
}

void	get_last_op(char *input, int *i, int *last)
{
	if (input[*i] == '|')
	{
		if (input[*i + 1] == '|')
		{
			*last = T_OR;
			(*i)++;
		}
		else
			*last = T_PIPE;
	}
	else if (input[*i] == '&')
	{
		if (input[*i + 1] == '&')
		{
			*last = T_AND;
			(*i)++;
		}
	}
	else
		*last = input[*i];
}

int	op_last_pos(char *input)
{
	int	i;
	int	before_last;
	int	last;

	i = 0;
	last = 0;
	if (!check_first(input))
		return (0);
	while (input[i])
	{
		before_last = last;
		if (!ft_isspace(input[i]))
		{
			get_last_op(input, &i, &last);
		}
		i++;
	}
	if (is_n_op(last) && !is_n_op(before_last))
		return (1);
	return (0);
}

void	append_to_prompt(char **input)
{
	char	*tmp;
	char	*join;
	char	*space;

	tmp = readline("Fill command: ");
	space = ft_strjoin(*input, " ");
	join = ft_strjoin(space, tmp);
	free(*input);
	free(tmp);
	free(space);
	*input = join;
}
