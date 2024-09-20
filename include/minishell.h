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
int	input_error(t_all *all);
int	ft_expander(t_all *all);
// ? init
void	init_shell(t_all *all);
// ? exit
void	del_token(t_all *all);
int		free_all(t_all *all);
// ? test
void	free_split(char **cmd);
// ? executor
int	use_built(t_all *all, int ch, char **cmd);
// ? utils/clean.c
int	clean_child(t_all *all);
// int	clean_child_b(t_all *all);
int	clean_child_b(t_all *all, char **token_str);
void	del_env(t_env **env);
int	close_fd(void);
// ? test_2.c
char	**create_envp(t_all *all);
char	*get_path(char *cmd, char **env);
// ? exit_status.c
void	get_exit_status(t_all *all);
// ? handle_redin.c
int	check_file(char *file, t_all *all);

#endif
