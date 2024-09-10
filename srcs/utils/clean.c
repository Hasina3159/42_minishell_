#include "../../include/minishell.h"

/*int	close_fd(void)
{
	int	fd;
	int	i;

	fd = 100;
	i = 5;
	while (i <= fd)
	{
		if (close(fd) == -1)
			fd--;
		else
			fd--;
	}
	return (0);
}*/

void	del_env(t_env **env)
{
	t_env	*tmp;
	t_env	*next;

	tmp = *env;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		tmp = next;
	}
	*env = NULL;
}

int	clean_child_b(t_all *all, char **token_str)
{
	// ?
	free_split(token_str);
	// ?
	free_all(all);
	return (0);
}

int	clean_child(t_all *all)
{
	del_token(all);
	free(all->cmd);
	rl_clear_history();
	del_env(&all->env);
	return (0);
}
