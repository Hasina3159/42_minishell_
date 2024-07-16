#include "../minishell.h"

void    ft_show_sanitized_command(t_all *all)
{
    int i;

    i = 0;
    while (i < all->token_count)
    {
        printf("%s ", all->tokens[i].value);
        i++;
    }
}