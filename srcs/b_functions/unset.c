#include "../minishell.h"


int	ft_unset(char **av, t_env **env)
{
	int	i;

	i = 1;
	while (av[i])
	{
		del_from_env(av[i], env);
		i++;
	}
	return (SUCCESS);
}
