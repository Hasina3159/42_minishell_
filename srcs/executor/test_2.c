#include "../../include/minishell.h"

int	env_size(t_env *env)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**create_envp(t_all *all)
{
	char 	**envp;
	t_env	*tmp;
	int		i;
	char	*join;

	tmp = all->env;
	if (!tmp)
		return (NULL);
	envp = malloc(sizeof(char *) * (env_size(all->env) + 1));
	if (envp == NULL)
		return (NULL);
	i = 0;
	while (tmp)
	{
		join = ft_strjoin(tmp->key, "=");
		envp[i] = ft_strjoin(join, tmp->value);
		free(join);
		i++;
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}

char	**get_env(char **env)
{
	int		i;
	char	*path;
	char	**env_path;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path = ft_strdup(env[i] + 5);
			break ;
		}
		i++;
	}
	if (!env[i])
	{
		// free(path);
		// path = NULL;
		return (NULL);
	}
	env_path = ft_split(path, ':');
	free(path);
	path = NULL;
	return (env_path);
}

char	*get_path(char *cmd, char **env)
{
	char	*path;
	char	*tmp;
	char	**env_path;
	int		i;

	i = 0;
	env_path = get_env(env);
	if (env_path == NULL)
		return (cmd);
	while (env_path[i])
	{
		tmp = ft_strjoin(env_path[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!access(path, F_OK) && !access(path, X_OK))
		{
			free_split(env_path);
			return (path);
		}
		else
			free(path);
		i++;
	}
	free_split(env_path);
	return (cmd);
}
