#include "../../include/minishell.h"

void	del_node(t_env *node, void (*del)(void *))
{
	del(node->key);
	del(node->value);
	del(node);
}

void	del_from_env(char *var, t_env **env)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = *env;
	prev = NULL;
	while (tmp)
	{
		if (!ft_strncmp(var, tmp->key, ft_strlen(var)))
		{
			if (prev == NULL)
				*env = tmp->next;
			else
				prev->next = tmp->next;
			del_node(tmp, free);
			break ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

int	ft_unset(t_all *all, char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		del_from_env(av[i], &all->env);
		i++;
	}
	return (SUCCESS);
}