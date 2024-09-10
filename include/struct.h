#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_token
{
	int				type;
	char			*value;
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
	// char			*value;
	t_token			tokens[TOKENS_MAX];
	int				token_count;
	t_env			*env;
	int				statloc;
	int				exit_status;
	int				child_pid;
	int				fd[2];
	int				tmp;
	int				has_pipe;
	// char			*last_cmd;
	int				sh;
	int				x;
	char			*hd_file;
}					t_all;

typedef struct s_dir
{
	char			*name;
	int				type;
	struct s_dir	*next;
}					t_dir;
#endif
