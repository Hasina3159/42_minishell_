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
