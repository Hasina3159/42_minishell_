#include "../minishell.h"

int	ft_setvaralue(t_all *all, char *key, char *value)
{
	t_env	*tmp;
	t_env	*new;

	tmp = all->env;
	while (tmp->next)
		tmp = tmp->next;
	new = (t_env *)malloc(sizeof(t_env));
	if (new == NULL)
		return (0);
	new->key = key;
	new->value = value;
	tmp->next = new;
	return (1);
}