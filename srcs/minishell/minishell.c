/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazafin <arazafin@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 18:16:35 by arazafin          #+#    #+#             */
/*   Updated: 2024/09/29 14:43:27 by arazafin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	clean_after_cmd(t_all *all)
{
	del_token(all);
	free(all->cmd);
}

int	read_line(char **input, t_all *all)
{
	if (isatty(STDIN_FILENO))
	{
		if (all->exit_status)
			*input = readline(BAD);
		else
			*input = readline(GOOD);
		if (*input == NULL)
			return (1);
		else if ((*input)[0] == '\0')
			return (1);
		else
			add_history(*input);
	}
	else
	{
		*input = NULL;
		return (1);
	}
	return (1);
}

int	main(void)
{
	int		i;
	t_all	all;

	signal(SIGINT, ft_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	init_shell(&all);
	while (1)
	{
		if (!read_line(&all.cmd, &all))
			continue ;
		if (all.cmd == NULL)
		{
			printf("exit\n");
			break ;
		}
		i = 0;
		if (!ft_tokenize(&all))
			ft_execute_all(&all, &i);
		clean_after_cmd(&all);
	}
	return (0);
}
