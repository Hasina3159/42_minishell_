#include "../minishell.h"

int ft_cd(int argc, char **argv)
{
    if (argc == 2)
        return (chdir(argv[1]));
    printf("cd : Too many arguments!\n");
    return (0);
}