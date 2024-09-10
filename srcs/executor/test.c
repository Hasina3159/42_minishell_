#include "../../include/minishell.h"

void	free_split(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != NULL)
	{
		free(cmd[i]);
		i++;
	}
	free(cmd);
}

/*char	*get_path(char *cmd)
{
	char	*path;
	char	*env;
	char	*tmp;
	char	**env_path;
	int		i;

	i = 0;
	env = getenv("PATH");
	env_path = ft_split(env, ':');
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
}*/

/*void	execve_cmd(char **cmd, char **envp)
{
	char	*path;
	int		error;

	path = get_path(cmd[0]);
	if (access(path, F_OK))
	{
		print_error(cmd[0], NULL, "command not found");
		free_split(cmd);
		exit(CMD_NOT_FOUND);
	}
	if (execve(path, cmd, envp) < 0)
	{
		error = errno;
		if (ft_isdir(path))
			print_error(path, NULL, strerror(EISDIR));
		else
			print_error(cmd[0], NULL, strerror(error));
		free_split(cmd);
		exit(126);
	}
}*/
void	execve_cmd(char **cmd, char **envp)
{
	char	*path;
	int		error;

	path = get_path(cmd[0], envp);
	if (access(path, F_OK))
	{
		print_error(cmd[0], NULL, "command not found");
		free_split(cmd);
		free_split(envp);
		exit(CMD_NOT_FOUND);
	}
	if (execve(path, cmd, envp) < 0)
	{
		error = errno;
		if (ft_isdir(path))
			print_error(path, NULL, strerror(EISDIR));
		else
			print_error(cmd[0], NULL, strerror(error));
		free_split(cmd);
		free_split(envp);
		exit(126);
	}
}
