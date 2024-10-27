/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazafin <arazafin@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 18:16:35 by arazafin          #+#    #+#             */
/*   Updated: 2024/10/25 08:31:34 by arazafin         ###   ########.fr       */
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
	(void)all;
	if (isatty(STDIN_FILENO))
	{
		*input = readline(PROMPT);
		if (*input == NULL)
			return (1);
		else if (ft_strlen(*input))
			add_history(*input);
		while (op_last_pos(*input))
		{
			if (append_to_prompt(input, all))
				return (0);
		}
		if (*input == NULL)
			return (1);
	}
	else
	{
		*input = NULL;
		return (0);
	}
	return (1);
}

void	clean_exit(t_all *all)
{
	del_env(&all->env);
	rl_clear_history();
	printf("exit\n");
	if (all->tmp > 0)
		close(all->tmp);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}

int	main(void)
{
	int		i;
	t_all	all;

	init_shell(&all);
	all.second = 0;
	while (1)
	{
		if (!read_line(&all.cmd, &all))
			continue ;
		if (all.cmd == NULL)
		{
			clean_exit(&all);
			exit(all.exit_status);
		}
		i = 0;
		if (!ft_tokenize(&all))
			ft_execute_all(&all, &i);
		clean_after_cmd(&all);
	}
	return (0);
}
