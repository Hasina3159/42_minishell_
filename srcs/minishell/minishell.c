#include "../../include/minishell.h"

int	read_line(char **input, t_all all)
{
	if(isatty(STDIN_FILENO))
	{
		if (all.exit_status)
			*input = readline(BAD);
		else
			*input = readline(GOOD);
		if (*input == NULL)
			return (0);
		else if ((*input)[0] == '\0')
			return (0);
		else
			add_history(*input);
	}
	else
	{
		*input = NULL;
		return (1);
	}
	return (1);
}

int	main(void)
{
	char	*cmd;
	int		i;
	t_all	all;

	signal(SIGINT, ft_ctrl_c);
	all.tmp = -1;
	all.exit_status = 0;
	while (1)
	{
		if (!read_line(&cmd, all))
			continue ;
		if (cmd == NULL)
		{
			printf("exit !\n");
			return (1);
		}
		ft_tokenize(&all, cmd);
		i = 0;
		if (!input_error(&all))
		{
			ft_expander(&all);
			ft_execute_all(&all, &i);
		}
		free(cmd);
	}
	return (0);
}
