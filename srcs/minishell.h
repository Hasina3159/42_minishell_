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
# include <unistd.h>

# define ERROR 0
# define SUCCESS 1
# define CMD_MAX 2048
# define TOKENS_MAX 255
# define T_COMMAND -1
# define T_WORD 0
# define T_STRING_S 1
# define T_STRING_D 17
# define T_OPERATOR 2
# define T_PIPE 3
# define T_IN 4
# define T_OUT 5
# define T_AND 6
# define T_OR 7
# define T_OUT_APPEND 8
# define T_HERE_DOC 9
# define T_P_OPEN 10
# define T_P_CLOSE 11
# define T_VAR 12
# define T_HD 13
# define T_FILE_IN 14
# define T_FILE_OUT 15
# define T_END 16

typedef struct s_token
{
	int				type;
	char			value[CMD_MAX];
}					t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_all
{
	size_t			i;
	int				in_quotes;
	char			current_token[CMD_MAX];
	int				token_index;
	char			quote_char;
	char			*cmd;
	char			*value;
	t_token			tokens[TOKENS_MAX];
	int				token_count;
	t_env			*env;
}					t_all;

//	b_functions
int					ft_echo(int argc, char **argv);
int					ft_cd(int argc, char **argv);
int					ft_pwd(int argc, char **argv);

// tokenizer
void				ft_init_t_all(t_all *all, char *cmd);
void				ft_add_token(t_all *all, int type, char *value);
int					ft_start_quotes(t_all *all);
int					ft_in_quotes_operation(t_all *all);
void				ft_sep_operation(t_all *all);
void				ft_set_operator(t_token *token);
void				ft_set_other(t_all *all);
void				ft_init_t_all(t_all *all, char *cmd);
void				ft_add_token(t_all *all, int type, char *value);
int					ft_is_sep(char c);
void				ft_tokenize(t_all *all);
void				ft_print_tokens(t_all *all);
char				*ft_show_token(t_token *token);
void				ft_set_command(t_all *all);
char				**ft_get_all_var(char *s);
void				ft_show_all_var(char **var);
int					ft_replace_all_vars(t_all *all);
int 				ft_replace_var(t_all *all, t_token *token);

//	minishell

//	parser

//	utils
int					ft_count_args(char **args);
int					ft_count_words(char const *s);
int					ft_strip_quotes(char **str);
int					ft_isspace(char c);
int					ft_is_sep(char c);
int					ft_is_operator(char c);
int					ft_count_occurences(char *text, char *sub);
int					ft_str_repl(char *text, char *from, char *to);
char				*ft_getvarvalue(t_all *all, char *var);
int					ft_setvarvalue(t_all *all, char *key, char *value);
int					ft_is_varchar(char c);
char				*ft_strndup(const char *s, int len);

#endif
