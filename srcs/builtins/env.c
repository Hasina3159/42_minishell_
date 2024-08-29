#include "../../include/minishell.h"

int	ft_env(t_all *all)
{
	int			i;
	extern char	**environ;
	char		*key;
	char		*value;
	t_env		*tmp;

	i = 0;
	while (environ[i])
	{
		key = ft_substr(environ[i], 0, ft_strchr(environ[i], '=') - environ[i]);
		value = ft_getvarvalue(all, key);
		if (ft_strlen(value) && !ft_is_in_env(all, key))
			printf("%s=%s\n", key, value);
		free(key);
		//free(value);
		i++;
	}
	tmp = all->env;
	while(tmp)
	{
		if (ft_strlen(tmp->value))
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (SUCCESS);
}
