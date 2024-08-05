#include "../minishell.h"

char	**ft_tokens_to_char(t_all *all, int *i)
{
	char	**token_str;
	int		len;
	int		old_i;
	int		j;

	len = 0;
	old_i = *i;
	while ((len + *i) < all->token_count && (all->tokens[len + *i].type == T_COMMAND
			|| all->tokens[len].type == T_WORD))
		len++;
	token_str = (char **)ft_calloc(len + 1, sizeof(char *));
	if (token_str == NULL)
		return (NULL);
	j = 0;
	while (*i < old_i + len && all->tokens[*i].type != T_END)
	{
		token_str[j] = ft_strdup(all->tokens[*i].value);
		*i = *i + 1;
		j++;
	}
	return (token_str);
}

int	ft_dup_stdin(const char *in)
{
	int	fd_in;

	if (in == NULL)
		return (0);
	printf("\nSTDIN\n");
	fd_in = open(in, O_RDONLY);
	if (fd_in == -1)
	{
		perror("open input");
		return (0);
	}
	if (dup2(fd_in, STDIN_FILENO) == -1)
	{
		perror("dup2 input");
		close(fd_in);
		return (0);
	}
	close(fd_in);
	return (1);
}

int	ft_dup_stdout(const char *out)
{
	int	fd_out;

	if (out == NULL)
		return (0);
	printf("\nSTDOUT\n");
	fd_out = open(out,  O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
	{
		perror("open output");
		return (0);
	}
	if (dup2(fd_out, STDOUT_FILENO) == -1)
	{
		perror("dup2 output");
		close(fd_out);
		return (0);
	}
	close(fd_out);
	return (1);
}

int	ft_child_exec(const char *in, const char *out, char **token_str)
{
	extern char	**environ;
	char		*cmd_with_path;

	ft_dup_stdin(in);
	ft_dup_stdin(out);
	for (int x = 0; token_str[x]; x++)
		printf("----> token[%d] : %s\n", x, token_str[x]);
	ft_dup_stdout(out);
	if (token_str[0])
		execve(token_str[0], token_str, environ);
	cmd_with_path = ft_strjoin("/bin/", token_str[0]);
	if (cmd_with_path)
	{
		printf("Trying command at /bin/: %s\n", cmd_with_path);
		execve(cmd_with_path, token_str, environ);
		free(cmd_with_path);
	}
	cmd_with_path = ft_strjoin("/usr/bin/", token_str[0]);
	if (cmd_with_path)
	{
		printf("Trying command at /usr/bin/: %s\n", cmd_with_path);
		execve(cmd_with_path, token_str, environ);
		free(cmd_with_path);
	}
	printf("%s: Command not found!\n", token_str[0]);
	return (-1);
}

int	ft_execute(t_all *all, int *i, const char *in, const char *out)
{
	char	**token_str;
	int		pid;
	int		fd[2];

	token_str = ft_tokens_to_char(all, i);
		ft_print_tokens(all);
	for(int x = 0; token_str[x]; x++)
		printf("TOKEN[%d] : %s\n", x, token_str[x]);
	if (token_str == NULL)
		return (1);
	pid = fork();
	if (pid == -1)
	{
		perror("Fork Error!");
		return (-1);
	}
	if (pipe(fd) == -1)
	{
		perror("Pipe Error!");
		return (-1);
	}
	if (pid == 0)
	{
		dup2(STDOUT_FILENO, fd[0]);
		ft_child_exec(in, out, token_str);
	}
	else
		wait(NULL);
	printf("\n TOKENS : %s\n", all->tokens[*i].value);
	if (all->tokens[*i].type == T_OUT || all->tokens[*i].type == T_OUT_APPEND)
		printf("--- OUT --- \n");
	return (-1);
}

char	*ft_get_out(t_all *all, int *i)
{
	int	j;

	j = *i;

	while (all->tokens[j].type == T_COMMAND || all->tokens[j].type == T_FILE_OUT || all->tokens[j].type == T_OUT)
		j++;
		
	if (all->tokens[j].type == T_FILE_OUT)
		return (all->tokens[j].value);
	return (NULL);
}

int	ft_execute_all(t_all *all, int *i)
{
	t_token *tokens;
	int		len;
	char	*in;
	char	*out;

	len = all->token_count;
	tokens = all->tokens;
	in = NULL;
	out = NULL;
	while (*i < len)
	{
		printf("IVELANY; i : %d, len : %d, type : %s\n", *i, len, ft_show_token(&tokens[*i]));
		if (tokens[*i].type == T_FILE_IN)
			in = tokens[*i].value;
		else if (tokens[*i].type == T_COMMAND)
		{
			out = ft_get_out(all, i);
			printf(">>>> in : %s, out : %s\n", in, out);
			ft_execute(all, i, in, out);
		}
		*i = *i + 1;
	}
	return (1);
}