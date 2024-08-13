#include "../minishell.h"


int	ft_unset(t_all *all, char **av)
{
	int		argc;

	argc = ft_count_splitted(av);
	if (argc != 2)
	{
		printf("Arguments count ERROR!\n");
		return (ERROR);
	}
	return (ft_setvarvalue(all, av[1], ""));
}
