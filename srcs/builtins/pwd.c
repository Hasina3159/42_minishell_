#include "../../include/minishell.h"

int	ft_pwd(t_all *all)
{
	char	pwd[TOKENS_MAX];
	int		error;

	(void)all;
	if (getcwd(pwd, TOKENS_MAX) == NULL)
	{
		error = errno;
		print_error("cd", NULL, strerror(error));
		return (ERROR);
	}
	printf("%s\n", pwd);
	return (SUCCESS);
}
