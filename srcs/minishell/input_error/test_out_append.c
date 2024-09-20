#include "../../../include/minishell.h"

int	test_out(t_token *tokens, int i)
{
	if (tokens[i + 1].type == T_OR)
	{
		print_error(NULL, NULL, "syntax error near unexpected token « | »");
		return (1);
	}
	else if (tokens[i + 1].type != T_FILE_OUT)
	{
		if (!ft_strncmp(tokens[i + 1].value, "&&", 3))
			print_error(NULL, NULL, "syntax error near unexpected token « & »");
		else
			print_error(NULL, NULL,
				"syntax error near unexpected token « newline »");
		return (1);
	}
	return (0);
}

int	test_out_append(t_token *tokens, int i)
{
	if (tokens[i + 1].type == T_OUT)
	{
		print_error(NULL, NULL, "syntax error near unexpected token « > »");
		return (1);
	}
	else if (tokens[i + 1].type == T_OUT_APPEND)
	{
		print_error(NULL, NULL, "syntax error near unexpected token « >> »");
		return (1);
	}
	else if (tokens[i + 1].type == T_END)
	{
		print_error(NULL, NULL,
			"syntax error near unexpected token « newline »");
		return (1);
	}
	return (0);
}

int	test_out_n_append(t_token *tokens, int i)
{
	int	ret;

	ret = 0;
	if (tokens[i].type == T_OUT)
	{
		ret = test_out(tokens, i);
		return (ret);
	}
	else if (tokens[i].type == T_OUT_APPEND)
	{
		ret = test_out_append(tokens, i);
		return (ret);
	}
	return (ret);
}
