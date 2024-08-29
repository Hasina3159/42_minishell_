#include "../../include/minishell.h"

void	print_error(char *name, char *arg, char *error)
{
	ft_putstr_fd(SH, 2);
	ft_putstr_fd(": ", 2);
	if (name != NULL)
	{
		ft_putstr_fd(name, 2);
		ft_putstr_fd(": ", 2);
	}
	if (arg != NULL)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(error, 2);
}
