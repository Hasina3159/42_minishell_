#include "../../include/minishell.h"

int	test_hd(t_token *tokens, int i)
{
	if (tokens[i + 1].type == T_IN)
		return (0);
	else if (tokens[i + 1].type == T_HD)
	{
		if (tokens[i + 2].type == T_HD)
			print_error(NULL, NULL, "syntax error near unexpected token « <<< »");
		else if (tokens[i + 2].type == T_IN)
			print_error(NULL, NULL, "syntax error near unexpected token « << »");
		else
			print_error(NULL, NULL, "syntax error near unexpected token « < »");
		return (1);
	}
	else if (tokens[i + 1].type != T_WORD && tokens[i + 1].type != T_COMMAND)
	{
		print_error(NULL, NULL, "syntax error near unexpected token « newline »");
		return (1);
	}
	return (0);
}

int	test_out(t_token *tokens, int i)
{
	if (tokens[i + 1].type == T_OR)
	{
		print_error(NULL, NULL, "syntax error near unexpected token « | »");
		return (1);
	}
	else if (tokens[i + 1].type != T_WORD && tokens[i + 1].type != T_COMMAND)
	{
		if (!ft_strncmp(tokens[i + 1].value, "&&", 3))
			print_error(NULL, NULL, "syntax error near unexpected token « & »");
		else
			print_error(NULL, NULL, "syntax error near unexpected token « newline »");
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
		print_error(NULL, NULL, "syntax error near unexpected token « newline »");
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
			print_error(NULL, NULL, "syntax error near unexpected token « && »");
			return (1);
		}
	}
	else if (tokens[i + 1].type != T_WORD)
	{
		print_error(NULL, NULL, "syntax error near unexpected token « newline »");
		return (1);
	}
	return (0);
}

int	test_t_pipe(t_token *tokens, int i)
{
	int	type;

	type = tokens[i + 1].type;
	if (type == T_AND)
	{
		print_error(NULL, NULL, "syntax error near unexpected token « |& »");
		return (1);
	}
	else if (type != T_WORD && type != T_COMMAND)
	{
		print_error(NULL, NULL, "syntax error near unexpected token « | »");
		return (1);
	}
	else if (i == 0)
	{
		print_error(NULL, NULL, "syntax error near unexpected token « | »");
		return (1);
	}
	return (0);
}

int	test_t_or(t_token *tokens, int i)
{
	if (tokens[i + 1].type != T_WORD && tokens[i + 1].type != T_COMMAND)
	{
		print_error(NULL, NULL, "syntax error near unexpected token « || »");
		return (1);
	}
	else if (i == 0)
	{
		print_error(NULL, NULL, "syntax error near unexpected token « || »");
		return (1);
	}
	return (0);
}

int	test_and(t_token *tokens, int i)
{
	if (tokens[i + 1].type != T_WORD && tokens[i + 1].type != T_COMMAND)
	{
		print_error(NULL, NULL, "syntax error near unexpected token « && »");
		return (1);
	}
	else if (i == 0)
	{
		print_error(NULL, NULL, "syntax error near unexpected token « && »");
		return (1);
	}
	return (0);
}

int	input_error(t_all *all)
{
	int	i;
	int	error;

	i = -1;
	error = 0;
	while (all->tokens[++i].type != T_END)
	{
		if (all->tokens[i].type == T_HD)
			error = test_hd(all->tokens, i);
		else if (all->tokens[i].type == T_OUT)
			error = test_out(all->tokens, i);
		else if (all->tokens[i].type == T_OUT_APPEND)
			error = test_out_append(all->tokens, i);
		else if (all->tokens[i].type == T_IN)
			error = test_in(all->tokens, i);
		else if (all->tokens[i].type == T_PIPE)
			error = test_t_pipe(all->tokens, i);
		else if (all->tokens[i].type == T_OR)
			error = test_t_or(all->tokens, i);
		else if (all->tokens[i].type == T_AND)
			error = test_and(all->tokens, i);
		if (error)
		{
			all->exit_status = 2;
			return (2);
		}
	}
	return (0);
}
