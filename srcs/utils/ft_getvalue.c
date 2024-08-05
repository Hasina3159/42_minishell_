#include "../minishell.h"

char    *ft_getvarvalue(t_all *all, char *var)
{
    t_env *tmp;

    tmp = all->env;
    while (tmp)
    {
        if (tmp->key == var)
            return (tmp->value);
        tmp = tmp->next;
    }
    if (getenv(var))
        return (getenv(var));
    return ("");
}