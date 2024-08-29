#include "../../include/minishell.h"

int ft_update_pwd(void)
{
    char *new_pwd = getcwd(NULL, 0);
    if (new_pwd == NULL)
    {
        perror("getcwd");
        return -1;
    }

    if (setenv("PWD", new_pwd, 1) == -1)
    {
        perror("setenv");
        free(new_pwd);
        return -1;
    }

    free(new_pwd);
    return 0;
}

int ft_cd(char **argv)
{
    int argc = ft_count_splitted(argv);
    char    *path;

    if (argc == 2)
    {
        path = argv[1];
    }
    else if (argc == 1)
    {
        path = getenv("HOME");
        if (path == NULL)
        {
            printf("cd: HOME not set\n");
            return -1;
        }
    }
    if (chdir(path) == -1)
	{
		printf("cd : ERROR!\n");
		return (ERROR);
	}
    return (ft_update_pwd());
}
