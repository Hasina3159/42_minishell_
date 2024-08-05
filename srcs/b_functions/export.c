# include "../minishell.h"

int    ft_strip_quotes(char **str)
{
	int 	len;
	char	*final;
	char	*s;

	s = *str;
	len = ft_strlen(s);
	printf(">>>>> \" : %d\n", ft_count_char(s, '\"'));
	printf(">>>>> ' : %d\n", ft_count_char(s, '\''));
	printf("-- s : %s, s[0] : %c, s[fin] : %c, len : %d\n", s, s[0], s[len - 1], len);
	if (ft_count_char(s, '\'') != 2 && ft_count_char(s, '\'') != 0)
		return (0);
	if (ft_count_char(s, '\"') != 2 && ft_count_char(s, '\"') != 0)
		return (0);
	if ((s[0] == '"' && s[len - 1] == '"') || (s[0] == '\'' && s[len - 1] == '\''))
	{
		final = ft_strdup(&s[1]);
		final[len - 2] = 0;
		printf(">>> FINAL : %s\n", final);
		free(s);
		*str = final;
	}
	return (1);
}

/*char    *ft_get_variable(char *s)
{
	
}*/

int	ft_export(int argc, char **argv)
{
	int	i;
	int line;

	line = 1;
	if (argc < 1 || argc > 2)
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
