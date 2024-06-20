# include "../minishell.h"

int ft_count_args(char **args)
{
    int i;

    i = 0;
    while (args && args[i])
        i++;
    return (i);
}