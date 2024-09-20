// #include "../../include/minishell.h"

// char	**ft_tokens_to_char(t_all *all, int *i)
// {
// 	char	**token_str;
// 	int		len;
// 	int		old_i;
// 	int		j;

// 	len = 0;
// 	old_i = *i;
// 	while ((len + *i) < all->token_count && (all->tokens[len
// 			+ *i].type == T_COMMAND || all->tokens[len + *i].type == T_WORD))
// 		len++;
// 	token_str = (char **)ft_calloc(len + 2, sizeof(char *));
// 	if (token_str == NULL)
// 		return (NULL);
// 	j = 0;
// 	while (*i < old_i + len && all->tokens[*i].type != T_END)
// 	{
// 		token_str[j] = ft_strdup(all->tokens[*i].value);
// 		*i = *i + 1;
// 		j++;
// 	}
// 	return (token_str);
// }

// int	ft_find_previous_command_index(t_token *tokens, int current_index)
// {
// 	int	i;

// 	i = current_index - 1;
// 	while (i >= 0)
// 	{
// 		if (tokens[i].type == T_COMMAND)
// 			return (i);
// 		i--;
// 	}
// 	return (-1);
// }

// int	is_last_cmd(t_all *all, int current_index)
// {
// 	if (current_index != all->token_count - 1)
// 		return (0);
// 	return (1);
// }

// void	ft_pipe(t_all *all)
// {
// 	int	in;

// 	if (all->infile)
// 	{
// 		in = open(all->infile, O_RDONLY);
// 		dup2(in, STDIN_FILENO);
// 		if (all->tmp != -1)
// 			close(all->tmp);
// 		if (all->hd_file)
// 		{
// 			if (!ft_strncmp(all->infile, all->hd_file, ft_strlen(all->infile)))
// 				unlink(all->hd_file);
// 		}
// 	}
// 	else if (all->tmp != -1)
// 	{
// 		if (dup2(all->tmp, STDIN_FILENO) == -1)
// 		{
// 			perror("dup2 tmp to stdin");
// 			exit(1);
// 		}
// 		close(all->tmp);
// 	}
// 	if (all->has_pipe)
// 	{
// 		if (dup2(all->fd[1], STDOUT_FILENO) == -1)
// 		{
// 			perror("dup2 fd[1] to stdout");
// 			exit(1);
// 		}
// 		close(all->fd[1]);
// 		close(all->fd[0]);
// 	}
// 	else
// 	{
// 		close(all->fd[0]);
// 		close(all->fd[1]);
// 	}
// }

// int	is_built(char **av)
// {
// 	if (!ft_strncmp(av[0], "echo", 5))
// 		return (1);
// 	else if (!ft_strncmp(av[0], "pwd", 4))
// 		return (2);
// 	else if (!ft_strncmp(av[0], "env", 4))
// 		return (3);
// 	else if (!ft_strncmp(av[0], "cd", 3))
// 		return (4);
// 	else if (!ft_strncmp(av[0], "export", 7))
// 		return (5);
// 	else if (!ft_strncmp(av[0], "unset", 6))
// 		return (6);
// 	else if (!ft_strncmp(av[0], "exit", 5))
// 		return (7);
// 	return (0);
// }

// int	use_built(t_all *all, int ch, char **cmd)
// {
// 	int	ac;

// 	ac = ft_count_splitted(cmd);
// 	if (ch == 1)
// 		return (ft_echo(ac, cmd));
// 	else if (ch == 2)
// 		return (ft_pwd(all));
// 	else if (ch == 3)
// 		return (ft_env(all));
// 	else if (ch == 4)
// 		return (ft_cd(cmd, all));
// 	else if (ch == 5)
// 		return (ft_export(all, cmd));
// 	else if (ch == 6)
// 		return (ft_unset(all, cmd));
// 	else if (ch == 7)
// 		return (ft_exit(all, cmd));
// 	return (126);
// }

// int	ft_child_exec_pipe(char **token_str, t_all *all)
// {
// 	char		**envp;
// 	int			ch;
// 	int			exit_s;

// 	if (all->child_pid == 0)
// 	{
// 		envp = create_envp(all);
// 		ft_pipe(all);
// 		ch = is_built(token_str);
// 		if (ch)
// 		{
// 			free_split(envp);
// 			exit_s = use_built(all, ch, token_str);
// 			clean_child_b(all, token_str);
// 			exit(exit_s);
// 		}
// 		clean_child(all);
// 		execve_cmd(token_str, envp);
// 	}
// 	return (0);
// }

// void	check_cmd(t_all *all, char **cmd, int *i)
// {
// 	int		ch;

// 	ch = is_built(cmd);
// 	if (ch && is_last_cmd(all, *i))
// 	{
// 		all->exit_status = use_built(all, ch, cmd);
// 	}
// 	else
// 	{
// 		all->child_pid = fork();
// 		if (all->child_pid == -1)
// 		{
// 			perror("fork");
// 			exit(1);
// 		}
// 		else if (all->child_pid == 0)
// 		{
// 			all->sh++;
// 			ft_child_exec_pipe(cmd, all);
// 		}
// 		else
// 		{
// 			if (all->has_pipe)
// 				all->tmp = all->fd[0];
// 			else
// 			{
// 			 	close(all->fd[0]);
// 				all->tmp = -1;
// 			}
// 			close(all->fd[1]);
// 		}
// 	}
// }

// int	ft_execute(t_all *all, int *i)
// {
// 	char	**token_str;

// 	token_str = ft_tokens_to_char(all, i);
// 	all->child_pid = -2;
// 	if (token_str == NULL)
// 		return (1);
// 	if (pipe(all->fd) == -1)
// 	{
// 		perror("Pipe Error!");
// 		return (-1);
// 	}
// 	all->has_pipe = ft_has_pipe_after(all, i);
// 	check_cmd(all, token_str, i);
// 	if (is_last_cmd(all, *i) && all->child_pid > 0)
// 	{
// 		get_exit_status(all);
// 		waitpid(-1, NULL, 0);
// 	}
// 	free_split(token_str);
// 	return (0);
// }

// char	*ft_get_out(t_all *all, int *i)
// {
// 	int	j;
// 	int	has_pipe;
// 	int	has_tee;

// 	j = *i;
// 	has_pipe = 0;
// 	has_tee = 0;
// 	while (all->tokens[j].type == T_COMMAND || all->tokens[j].type == T_WORD
// 		|| all->tokens[j].type == T_OUT)
// 		j++;
// 	if (all->tokens[j].type == T_PIPE)
// 		j++;
// 	if (!ft_strncmp(all->tokens[j].value, "/usr/bin/tee", 13))
// 		has_tee = 1;
// 	while (all->tokens[j].type == T_COMMAND || all->tokens[j].type == T_WORD
// 		|| all->tokens[j].type == T_OUT)
// 		j++;
// 	if (all->tokens[j].type == T_PIPE)
// 		has_pipe = 1;
// 	if (has_tee && !has_pipe)
// 		return (all->tokens[j].value);
// 	return (NULL);
// }

// int	is_n_op(int type)
// {
// 	if (type == T_PIPE)
// 		return (1);
// 	else if (type == T_OR)
// 		return (1);
// 	else if (type == T_AND)
// 		return (1);
// 	else if (type == T_END)
// 		return (1);
// 	return (0);
// }

// int	ft_has_pipe_after(t_all *all, int *i)
// {
// 	int	j;

// 	j = *i;
// 	while (!is_n_op(all->tokens[j].type))
// 		j++;
// 	if (all->tokens[j].type == T_PIPE)
// 		return (1);
// 	return (0);
// }

// int	ft_has_op_before(t_all *all, int *i, int type)
// {
// 	int	j;

// 	j = *i;
// 	while (j > 0 && (all->tokens[j].type == T_FILE_IN
// 			|| all->tokens[j].type == T_IN || all->tokens[j].type == T_COMMAND
// 			|| all->tokens[j].type == T_WORD))
// 		j--;
// 	if (all->tokens[j].type == type)
// 		return (1);
// 	return (0);
// }

// int	exec_cmd(t_all *all, int *i)
// {
// 	if (all->exit_status && *i > 1 && (ft_has_op_before(all, i, T_AND)))
// 		return (0);
// 	else if (!all->exit_status && *i > 1 && (ft_has_op_before(all, i,
// 				T_OR)))
// 		return (0);
// 	ft_execute(all, i);
// 	return (2);
// }

// int	ft_execute_all(t_all *all, int *i)
// {
// 	t_token	*tokens;
// 	int		len;
// 	int		x;

// 	len = all->token_count;
// 	tokens = all->tokens;
// 	x = 0;
// 	while (*i < len)
// 	{
// 		if (!x)
// 		{
// 			all->infile = get_infile(all, *i);
// 			x = 1;
// 		}
// 		if (tokens[*i].type == T_COMMAND)
// 		{
// 			if (exec_cmd(all, i) == 0)
// 				break ;
// 			x = 0;
// 		}
// 		while (!is_n_op(tokens[*i].type))
// 			*i = *i + 1;
// 		*i = *i + 1;
// 	}
// 	return (1);
// }
