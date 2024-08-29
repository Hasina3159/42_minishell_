#include "../../include/minishell.h"

int	check_exit_arg(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (ft_isdigit(arg[i]) == 0)
		{
			print_error("exit", arg, "numeric argument required");
			close(STDIN_FILENO);
			close(STDOUT_FILENO);
			close(STDERR_FILENO);
			exit(2);
		}
		i++;
	}
	return (0);
}
void	ft_exit(t_all *all, char **argv)
{
	int	argc;

	argc = ft_count_splitted(argv);
	printf("exit\n");
	if (argc == 1)
	{
		rl_clear_history();
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
		exit(all->exit_status);
	}
	else if (argc == 2)
	{
		rl_clear_history();
		check_exit_arg(argv[1]);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
		exit (ft_atoi(argv[1]));
	}
	else
		print_error("exit", NULL, "too much arguments");
}
