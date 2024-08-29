#include "../../include/minishell.h"

char	*join_arg(char **av, int i)
{
	char	*tmp;
	char	*out;

	out = NULL;
	while (av[i])
	{
		if (!out)
			out = ft_strjoin(av[i], " ");
		else
		{
			tmp = ft_strjoin(out, av[i]);
			free(out);
			out = ft_strjoin(tmp, " ");
			free(tmp);
		}
		i++;
	}
	return (out);
}

int	check_flag(int ac, char **av, int *nl)
{
	if (ac > 1)
	{
		if (!ft_strncmp("-n", av[1], ft_strlen("-n")))
		{
			*nl = 0;
			return (2);
		}
		else
		{
			*nl = 1;
			return (1);
		}
	}
	return (1);
}

int	ft_echo(int argc, char **argv)
{
	int		nl;
	int		i;
	char	*to_print;

	if (argc == 1)
	{
		printf("\n");
		return (SUCCESS);
	}
	i = check_flag(argc, argv, &nl);
	to_print = join_arg(argv, i);
	if (to_print != NULL)
	{
		printf("%s", to_print);
		free(to_print);
	}
	if (nl)
		printf("\n");
	return (SUCCESS);
}
