#include "../minishell.h"

t_env	*ft_create_env(char *key, char *value)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	new->key = key;
	new->value = value;
	return (new);
}

int	ft_setvarvalue(t_all *all, char *key, char *value)
{
	t_env	*tmp;
	t_env	*new;

	tmp = all->env;
	if (tmp == NULL)
	{
		all->env = ft_create_env(key, value);
		return (0);
	}
	while (tmp && tmp->next)
	{
		if (!ft_strncmp(tmp->key, key, ft_strlen(key)))
		{
			tmp->value = value;
			return (0);
		}
		tmp = tmp->next;
	}
	new = (t_env *)malloc(sizeof(t_env));
	if (new == NULL)
		return (0);
	new->key = key;
	new->value = value;
	tmp->next = new;
	return (1);
}
