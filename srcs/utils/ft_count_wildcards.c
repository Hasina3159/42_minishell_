#include "../minishell.h"

int ft_count_wildcards(char *w)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (w[i])
    {
        if (w[i] == '*')
        {
            while (w[i] && w[i] == '*')
                i++;
            count++;
        }
        i++;
    }
    return (count);
}