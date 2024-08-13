#include "../minishell.h"

void	ft_exit(t_all *all, char **argv)
{
	int	argc;

	argc = ft_count_splitted(argv);
	if (argc == 1)
	{
		rl_clear_history();
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
		exit(all->exit_status);
		exit (0);
	}
	else if (argc == 2)
	{
		rl_clear_history();
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
		exit(all->exit_status);
		exit (ft_atoi(argv[1]));
	}
	//close(exe.old_io[0]);
	//close(exe.old_io[1]);
}
