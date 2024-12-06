/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:24:06 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/12/06 10:24:07 by ntodisoa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_child_exec_pipe(char **token_str, t_all *all)
{
	char		**envp;
	int			ch;
	int			exit_s;

	if (ft_pipe(all))
	{
		clean_child_b(all, token_str);
		exit(1);
	}
	ch = is_built(token_str);
	if (ch)
	{
		exit_s = use_built(all, ch, token_str);
		clean_child_b(all, token_str);
		exit(exit_s);
	}
	envp = create_envp(all);
	clean_child(all);
	setup_child_signals();
	execve_cmd(token_str, envp);
	return (0);
}

void	check_cmd(t_all *all, char **cmd, int *i)
{
	int		ch;

	ch = is_built(cmd);
	if (ch && !all->has_pipe && !all->has_out
		&& !ft_has_op_before(all, i, T_PIPE))
		all->exit_status = use_built(all, ch, cmd);
	else
	{
		setup_parent_signals();
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
	if (token_str == NULL
		|| (all->exit_status == 130 && all->hd_file))
	{
		if (check_redin(all))
			return (1);
		all->exit_status = 0;
		return (1);
	}
	if (pipe(all->fd) == -1)
	{
		perror("Pipe Error!");
		return (-1);
	}
	check_cmd(all, token_str, i);
	if ((all->has_pipe == 0 && all->child_pid > 0) || ft_has_op_after(all, i))
		get_exit_status(all);
	free_split(token_str);
	return (0);
}

int	exec_cmd(t_all *all, int *i)
{
	all->pos = *i;
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
	int		ret;

	len = all->token_count;
	tokens = all->tokens;
	ret = 0;
	reset_redirection(all, &x);
	while (*i < len)
	{
		check_redir(all, i, &x, &ret);
		if (tokens[*i].type == T_COMMAND || is_n_op(tokens[*i].type))
		{
			if (exec_cmd(all, i) == 0)
				break ;
			reset_redirection(all, &x);
			if (ret == 2)
				return (2);
		}
		*i = *i + 1;
	}
	return (1);
}
