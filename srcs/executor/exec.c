/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazafin <arazafin@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 11:13:47 by arazafin          #+#    #+#             */
/*   Updated: 2024/10/12 08:32:36 by arazafin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_child_exec_pipe(char **token_str, t_all *all)
{
	char		**envp;
	int			ch;
	int			exit_s;

	if (all->child_pid == 0)
	{
		if (ft_pipe(all))
		{
			clean_child(all);
			exit(1);
		}
		envp = create_envp(all);
		ch = is_built(token_str);
		if (ch)
		{
			free_split(envp);
			exit_s = use_built(all, ch, token_str);
			clean_child_b(all, token_str);
			exit(exit_s);
		}
		clean_child(all);
		execve_cmd(token_str, envp);
	}
	return (0);
}

void	check_cmd(t_all *all, char **cmd)
{
	int		ch;

	ch = is_built(cmd);
	if (ch && !all->has_pipe && !all->has_in && !all->has_out)
		all->exit_status = use_built(all, ch, cmd);
	else
	{
		all->child_pid = fork();
		if (all->child_pid == -1)
		{
			perror("fork");
			exit(1);
		}
		else if (all->child_pid == 0)
		{
			all->sh++;
			ft_child_exec_pipe(cmd, all);
		}
		else
			parent_process(all);
	}
}

int	ft_execute(t_all *all, int *i)
{
	char	**token_str;

	token_str = ft_tokens_to_char(all, i);
	all->child_pid = -2;
	if (token_str == NULL)
		return (1);
	if (pipe(all->fd) == -1)
	{
		perror("Pipe Error!");
		return (-1);
	}
	check_cmd(all, token_str);
	if (!all->has_pipe && all->child_pid > 0)
	{
		get_exit_status(all);
		waitpid(-1, NULL, 0);
	}
	free_split(token_str);
	return (0);
}

int	exec_cmd(t_all *all, int *i)
{
	if (all->exit_status && *i > 1 && (ft_has_op_before(all, i, T_AND)))
		return (0);
	else if (!all->exit_status && *i > 1 && (ft_has_op_before(all, i,
				T_OR)))
		return (0);
	ft_execute(all, i);
	return (2);
}

int	ft_execute_all(t_all *all, int *i)
{
	t_token	*tokens;
	int		len;
	int		x;

	len = all->token_count;
	tokens = all->tokens;
	reset_redirection(all, &x);
	while (*i < len)
	{
		if (!x)
		{
			is_need_pipe(all, i);
			all->outfile = get_outfile(all, *i);
			all->infile = get_infile(all, *i);
			x = 1;
		}
		if (tokens[*i].type == T_COMMAND)
		{
			if (exec_cmd(all, i) == 0)
				break ;
			reset_redirection(all, &x);
		}
		*i = *i + 1;
	}
	return (1);
}
