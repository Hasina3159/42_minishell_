#ifndef MINISHELL_H
# define MINISHELL_H


# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <dirent.h>

# define ERROR 0
# define SUCCESS 1

//	b_functions
int	ft_echo(int argc, char **argv);
int ft_cd(int argc, char **argv);
int ft_pwd(int argc, char **argv);


//	minishell


//	parser


//	utils
int ft_count_args(char **args);


# endif
