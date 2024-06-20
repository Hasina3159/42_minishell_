# include "../minishell.h"

int	ft_echo(char **args)
{
	int	i;
	int line;
	int	len;

	line = 1;
	len = ft_count_args(args);
	if (len < 1)
	{
		printf("\n");
		return (SUCCESS);
	}
	i = 1;
	if (ft_strncmp("-n", args[1], ft_strlen(args[1])))
	{
		line = 0;
		i++;
	}
	while (i < len)
	{
		printf(args[i]);
		i++;
	}
	if (line)
		printf("\n");
	return (SUCCESS);
}
