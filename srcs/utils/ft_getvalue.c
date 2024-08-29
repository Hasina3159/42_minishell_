#include "../../include/minishell.h"

char	*ft_getvarvalue(t_all *all, char *var)
{
	t_env	*tmp;

    //printf("[GETVARVALUE]\n");
	tmp = all->env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, var, ft_strlen(var)))
			return (tmp->value);
		tmp = tmp->next;
	}
	if (getenv(var))
		return (getenv(var));
	return ("");
}

char	*ft_is_in_env(t_all *all, char *var)
{
	t_env	*tmp;

	tmp = all->env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, var, ft_strlen(var)))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}
