#include "../minishell.h"

void	ft_ctrl_c(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ft_ctrl_slash(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
