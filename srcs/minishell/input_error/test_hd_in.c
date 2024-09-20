#include "../../../include/minishell.h"

static int	t_out(t_token *tokens, int i)
{
	if (tokens[i + 2].type == T_OUT)
	{
		print_error(NULL, NULL, "syntax error near unexpected token « > »");
		return (1);
	}
	else if (tokens[i + 2].type == T_OUT_APPEND)
	{
		print_error(NULL, NULL, "syntax error near unexpected token « >> »");
		return (1);
	}
	else
		return (1);
}

static int	t_hd(t_token *tokens, int i)
{
	if (tokens[i + 2].type == T_HD)
		print_error(NULL, NULL, "syntax error near unexpected token « <<< »");
	else if (tokens[i + 2].type == T_IN)
		print_error(NULL, NULL, "syntax error near unexpected token « << »");
	else
		print_error(NULL, NULL, "syntax error near unexpected token « < »");
	return (1);
}

int	test_hd(t_token *tokens, int i)
{
	if (tokens[i + 1].type == T_IN)
	{
		if (t_out(tokens, i))
			return (1);
	}
	else if (tokens[i + 1].type == T_HD)
	{
		if (t_hd(tokens, i))
			return (1);
	}
	else if (tokens[i + 1].type != T_HD_ENDER)
	{
		print_error(NULL, NULL,
			"syntax error near unexpected token « newline »");
		return (1);
	}
	return (0);
}

int	test_in(t_token *tokens, int i)
{
	if (tokens[i + 1].type == T_PIPE)
	{
		print_error(NULL, NULL, "syntax error near unexpected token « | »");
		return (1);
	}
	else if (tokens[i + 1].type == T_OR)
	{
		print_error(NULL, NULL, "syntax error near unexpected token « || »");
		return (1);
	}
	else if (tokens[i + 1].type == T_AND)
	{
		if (ft_strncmp(tokens[i + 1].value, "&&", 2))
		{
			print_error(NULL, NULL,
				"syntax error near unexpected token « && »");
			return (1);
		}
	}
	else if (tokens[i + 1].type != T_FILE_IN)
	{
		print_error(NULL, NULL,
			"syntax error near unexpected token « newline »");
		return (1);
	}
	return (0);
}

int	test_hd_in(t_token *tokens, int i)
{
	int	ret;

	ret = 0;
	if (tokens[i].type == T_HD)
	{
		ret = test_hd(tokens, i);
		return (ret);
	}
	else if (tokens[i].type == T_IN)
	{
		ret = test_in(tokens, i);
		return (ret);
	}
	return (ret);
}