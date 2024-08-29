// #include "../../include/minishell.h"

// int	is_built(char **av)
// {
// 	if (!ft_strncmp(av[0], "echo", 5))
// 		return (1);
// 	else if (!ft_strncmp(av[0], "cd", 3))
// 		return (2);
// 	else if (!ft_strncmp(av[0], "pwd", 4))
// 		return (3);
// 	else if (!ft_strncmp(av[0], "export", 7))
// 		return (4);
// 	else if (!ft_strncmp(av[0], "unset", 6))
// 		return (5);
// 	else if (!ft_strncmp(av[0], "env", 4))
// 		return (6);
// 	else if (!ft_strncmp(av[0], "exit", 5))
// 		return (7);
// 	return (0);
// }

// void	use_built(t_all *all, int ch, char **cmd)
// {
// 	int	ac;

// 	ac = ft_count_splitted(cmd);
// 	if (ch == 1)
// 		all->exit_status = ft_echo(ac, cmd);
// 	else if (ch == 2)
// 		all->exit_status = ft_cd(cmd);
// 	else if (ch == 3)
// 		all->exit_status = ft_pwd(ac, cmd);
// 	else if (ch == 4)
// 		all->exit_status = ft_export(all, cmd);
// 	else if (ch == 5)
// 		all->exit_status = ft_unset(all, cmd);
// 	else if (ch == 6)
// 		all->exit_status = ft_env(all);
// 	else if (ch == 7)
// 		ft_exit(all, cmd);
// }

// void	check_cmd(t_all *all, char **cmd, int *i)
// {
// 	int		ch;

// 	ch = is_built(cmd);
// 	if (ch != 0)
// 		use_built(all, ch, cmd);
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
// 			all->x = *i;
// 			ft_child_exec_pipe(cmd, all, i);
// 		}
// 		else
// 		{
// 			waitpid(all->child_pid, NULL, 0);
// 			if (all->has_pipe)
// 				all->tmp = all->fd[0];
// 			close(all->fd[1]);
// 		}
// 	}
// }
