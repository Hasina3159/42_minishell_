/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazafin <arazafin@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 19:59:21 by arazafin          #+#    #+#             */
/*   Updated: 2024/10/12 17:09:14 by arazafin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	op_last_pos(char *input)
{
	int	i;
	int	last;

	i = 0;
	while (input[i])
	{
		if (!ft_isspace(input[i]))
			last = input[i];
		i++;
	}
	if ((char)last == '|')
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
