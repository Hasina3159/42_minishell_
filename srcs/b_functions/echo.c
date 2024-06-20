# include "../minishell.h"

int	ft_echo(int argc, char **argv)
{
	int	i;
	int line;

	line = 1;
	if (argc < 1)
	{
		printf("\n");
		return (SUCCESS);
	}
	i = 1;
	if (!ft_strncmp("-n", argv[1], ft_strlen(argv[1])))
	{
		line = 0;
		i++;
	}
	while (i < argc)
	{
		printf("%s", argv[i]);
		i++;
	}
	if (line)
		printf("\n");
	return (SUCCESS);
}
