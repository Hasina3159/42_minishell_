#include "../../include/minishell.h"

void	get_exit_status(t_all *all)
{
	int	sig;

	sig = 0;
	waitpid(all->child_pid, &all->statloc, 0);
	if (WIFEXITED(all->statloc))
		all->exit_status = WEXITSTATUS(all->statloc);
	else if (WIFSIGNALED(all->statloc))
	{
		sig = WTERMSIG(all->statloc);
		if (sig == SIGINT)
			all->exit_status = 130;
	}
}
