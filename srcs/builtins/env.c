#include "../../include/minishell.h"

int	ft_env(t_all *all)
{
	t_env		*tmp;

	tmp = all->env;
	while(tmp)
	{
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (SUCCESS);
}
