/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:30:02 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/12/21 14:36:26 by ntodisoa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_write_to_file(const char *filename, const char *text)
{
	int		fd;
	int		bytes_written;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (0);
	bytes_written = write(fd, text, ft_strlen(text));
	if (bytes_written == -1)
	{
		close(fd);
		return (0);
	}
	if (close(fd) == -1)
		return (0);
	return (1);
}

void	clean_after_cmd(t_all *all)
{
	del_token(all);
	free(all->cmd);
	if (all->hd_file)
	{
		unlink(all->hd_file);
		free(all->hd_file);
		all->hd_file = NULL;
	}
}

int	read_line(char **input, t_all *all)
{
	if (isatty(STDIN_FILENO))
	{
		*input = readline(PROMPT);
		if (*input == NULL)
			return (1);
		else if (ft_strlen(*input))
		{
			add_history(*input);
			ft_write_to_file(HISTORY, *input);
			ft_write_to_file(HISTORY, "\n");
		}
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
	if (all->hd_file)
	{
		unlink(all->hd_file);
		free(all->hd_file);
		all->hd_file = NULL;
	}
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
	int				i;
	static t_all	all;

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
