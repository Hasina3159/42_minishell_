/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:31:01 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/12/07 12:36:13 by ntodisoa         ###   ########.fr       */
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
		if (!ft_isspace(input[i]))
		{
			before_last = last;
			get_last_op(input, &i, &last);
		}
		i++;
	}
	if (is_n_op(last) && !is_n_op(before_last))
		return (1);
	return (0);
}

void	is_ctrl_d(char *tmp, t_all *all)
{
	if (!tmp)
	{
		del_env(&all->env);
		free(all->cmd);
		print_error("syntax error", NULL, "unexpected end of file");
		exit(2);
	}
}

int	append_to_prompt(char **input, t_all *all)
{
	char	*tmp;
	char	*join;
	char	*space;
	char	*in_std;

	in_std = ttyname(STDIN_FILENO);
	all->second = 1;
	tmp = readline("Fill command: ");
	if (all->exit_status == 130)
	{
		free(*input);
		new_std(in_std);
		all->second = 0;
		return (1);
	}
	is_ctrl_d(tmp, all);
	space = ft_strjoin(*input, " ");
	join = ft_strjoin(space, tmp);
	free(*input);
	free(tmp);
	free(space);
	*input = join;
	return (0);
}
