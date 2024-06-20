#include "../minishell.h"

int	main(void)
{
	char *input;
	char cwd[1024];

	while (1)
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
			printf("%s", cwd);
			input = readline("> ");
			printf("%s\n", input);
		}
		else
		{
			printf("Current direcory read Error!\n");
			return (0);
		}
	}
	return (0);
}