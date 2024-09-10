#include "../../include/minishell.h"

int ft_count_splitted(char **splitted)
{
	int i;

	if (!splitted)
		return (0);
	i = 0;
	while (splitted[i])
		i++;
	return (i);
}
