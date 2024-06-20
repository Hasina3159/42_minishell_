#include "../minishell.h"

int	main(void)
{
	int		argc;
	char	**argv;
	char	*input;
	//char	**pwd;

	//pwd = ft_split("pwd", ' ');
	while (1)
	{
		//ft_pwd(1, pwd);
		input = readline("> ");
		printf("%s\n", input);
		argv = ft_split(input, ' ');
		argc = ft_count_args(argv);
		if (!ft_strncmp(argv[0], "echo", ft_strlen("echo")))
			ft_echo(argc, argv);
		if (!ft_strncmp(argv[0], "cd", ft_strlen("cd")))
			ft_cd(argc, argv);
		if (!ft_strncmp(argv[0], "pwd", ft_strlen("pwd")))
			ft_pwd(argc, argv);
		free(input);
		continue;
	}
	return (0);
}