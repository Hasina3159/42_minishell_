#include "../../include/minishell.h"

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
	return (0);
}
/*
int	ft_pwd(t_all *all)
{
	t_env	*env;

	env = all->env;
	while (env)
	{
		if (!ft_strncmp(env->key, "PWD", 4))
			break ;
		env = env->next;
	}
	printf("%s\n", env->value);
	return (0);
}*/
