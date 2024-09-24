#include "../../include/minishell.h"

int	check_file(char *file, t_all *all, int f)
{
	if (f == 0)
	{
		if (access(file, F_OK) < 0)
		{
			if (all->sh)
				print_error(NULL, file, "No such file or directory");
			return (1);
		}
		if (access(file, R_OK) < 0)
		{
			if (all->sh)
				print_error(NULL, file, "Permission denied");
			return (1);
		}
	}
	else if (f == 1)
	{
		if (access(file, W_OK) < 0)
		{
			if (all->sh)
				print_error(NULL, file, "Permission denied");
			return (1);
		}
	}
	return (0);
}

static int	f_op(int type)
{
	if (type == T_PIPE || type == T_END || type == T_OR || type == T_AND)
		return (1);
	return (0);
}

char	*get_infile(t_all *all, int i)
{
	char	*in;
	int		check;
	int		x;

	in = NULL;
	check = 0;
	x = i;
	while (!f_op(all->tokens[x].type))
	{
		if (all->tokens[x].type == T_HD)
		{
			if (all->hd_file)
			{
				unlink(all->hd_file);
				free(all->hd_file);
				all->hd_file = NULL;
			}
			heredoc(all, all->tokens[x + 1].value);
			if (!check)
				in = all->hd_file;
		}
		else if (all->tokens[x].type == T_IN)
		{
			if (all->hd_file)
			{
				unlink(all->hd_file);
				free(all->hd_file);
				all->hd_file = NULL;
			}
			if (!check)
				in = all->tokens[x + 1].value;
			if (check_file(all->tokens[x + 1].value, all, 0))
				check = 1;
		}
		x++;
	}
	return (in);
}
