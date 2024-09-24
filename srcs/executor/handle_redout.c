#include "../../include/minishell.h"

int	open_outfile(t_all *all, int type)
{
	int	fd;

	if (type == 1)
		fd = open(all->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	else if (type == 2)
		fd = open(all->outfile, O_CREAT | O_WRONLY | O_APPEND, 0777);
	return (fd);
}

static int	f_op(int type)
{
	if (type == T_PIPE || type == T_END || type == T_OR || type == T_AND)
		return (1);
	return (0);
}

char	*get_outfile(t_all *all, int i)
{
	char	*out;
	int		check;
	int		x;
	int		fd;

	out = NULL;
	check = 0;
	x = i;
	all->out_type = 0;
	while (!f_op(all->tokens[x].type))
	{
		if (all->tokens[x].type == T_OUT && !check)
		{
			out = all->tokens[x + 1].value;
			fd = open(out, O_CREAT | O_WRONLY | O_TRUNC, 0777);
			if (check_file(out, all, 1))
				check = 1;
			ft_putchar_fd('\0', fd);
			close(fd);
			all->out_type = 1;
		}
		else if (all->tokens[x].type == T_OUT_APPEND && !check)
		{
			out = all->tokens[x + 1].value;
			fd = open(out, O_CREAT | O_WRONLY | O_APPEND, 0777);
			if (check_file(out, all, 1))
				check = 1;
			close(fd);
			all->out_type = 2;
		}
		x++;
	}
	return (out);
}

