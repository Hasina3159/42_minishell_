#include "../minishell.h"

int	ft_is_varchar(char c)
{
	if (!ft_isalnum(c) && c != '_')
		return (0);
	return (1);
}