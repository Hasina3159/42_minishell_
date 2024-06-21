#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdlib.h>
# include <unistd.h>

# define ERROR 0
# define SUCCESS 1

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

//	b_functions
int					ft_echo(int argc, char **argv);
int					ft_cd(int argc, char **argv);
int					ft_pwd(int argc, char **argv);

//	minishell

//	parser

//	utils
int					ft_count_args(char **args);
int				ft_count_words(char const *s);

#endif
