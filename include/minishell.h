#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <dirent.h>
# include <sys/syscall.h>
# include <string.h>
# include <errno.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include "../libft/libft.h"
# include "define.h"
# include "struct.h"
# include "builtins.h"
# include "executor.h"
# include "utils.h"
# include "tokenizer.h"

// readline
// int	read_line(char **input, t_ex exe);
// void				free_cmd(t_ex ex);
int	input_error(t_all *all);
int	ft_expander(t_all *all);

#endif
