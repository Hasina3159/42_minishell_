#include "../../include/minishell.h"

char	*ft_strndup(const char *s, int len)
{
	char *final;
	int i;

	final = (char *)ft_calloc(len + 1, sizeof(char));
	if (final == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		final[i] = s[i];
		i++;
	}
	return (final);
}
