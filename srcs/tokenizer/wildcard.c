#include "../minishell.h"

int ft_match_one(char *s, char next, int *count)
{
	int	i;

	i = 0;
	*count = *count + 1;
	while (s[i])
	{
		if (s[i] == next)
			return (i);
		i++;
	}
	if (s[i] == next)
		return (i);
	printf("s : [%c], next : [%c]\n", s[i], next);
	return (-1);
}

int	ft_match(char *s, char *w, int n)
{
	int	i;
	int	j;
	int	count;
	int	ok;

	i = 0;
	j = 0;
	count = 0;
	ok = 0;
	while (w[i])
	{
		ok = 0;
		if (count >= n)
			return (1);
		if ((w[i] != '*' && w[i] != s[j]))
			return (0);
		if (w[i] == '*')
			ok = ft_match_one(&s[j], w[i + 1], &count);
		if (ok == -1)
			return (0);
		else if (ok != 0)
			j = j + ok - 1;
		j++;
		i++;
	}
	return (1);
}
