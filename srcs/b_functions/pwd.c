#include "../minishell.h"

int	ft_pwd(int argc, char **argv)
{
	char path[1024];

	if (getcwd(path, sizeof(path)) == NULL || ft_strncmp("pwd", argv[0],
			ft_strlen("pwd")) || argc != 1)
	{
		printf("pwd : Too many arguments!, path : %s, argc : %d, argv[0] : %s, cmp : %d\n", path,
			argc, argv[0], ft_strncmp("pwd", argv[0],
			ft_strlen("pwd")));
		return (0);
	}
	printf("%s\n", path);
	return (1);
}