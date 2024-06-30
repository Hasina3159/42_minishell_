#include "../minishell.h"

/*int	main(void)
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
		argv = ft_split(input, ' ');
		argc = ft_count_args(argv);
		if (!ft_strncmp(argv[0], "echo", ft_strlen("echo")))
			ft_echo(argc, argv);
		if (!ft_strncmp(argv[0], "cd", ft_strlen("cd")))
			ft_cd(argc, argv);
		if (!ft_strncmp(argv[0], "pwd", ft_strlen("pwd")))
			ft_pwd(argc, argv);
		printf("COUNT : %d\n", ft_count_words(input));
		printf("STRIP : %d\n", ft_strip_quotes(&argv[0]));
		printf("ARGV[0] : %s\n", argv[0]);
		free(input);
		continue;
	}
	return (0);
}*/