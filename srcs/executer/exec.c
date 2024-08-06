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
			|| all->tokens[len + *i].type == T_WORD))
		len++;
	token_str = (char **)ft_calloc(len + 2, sizeof(char *));
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

int	ft_dup_stdin(const char *in, char **tokens_str)
{
	int	i;

	if (in == NULL)
		return (0);
	i = 0;
	while (tokens_str[i])
		i++;
	tokens_str[i] = ft_strdup(in);
	return (1);
}

int	ft_dup_stdout(const char *out)
{
	int	fd_out;

	if (out == NULL)
		return (0);
	printf("\n ----------------------------- STDOUT ----------------------------- \n");
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

int	ft_child_exec_pipe(const char *in, const char *out, char **token_str, t_all *all)
{
	extern char	**environ;
	char		*cmd_with_path;

	printf("PIPE\n");
	ft_dup_stdin(in, token_str);
	ft_dup_stdout(out);
	if (all->child_pid == 0)
	{
		if (all->tmp != -1)
		{
			dup2(all->tmp, STDIN_FILENO);
			close(all->tmp);
		}
		if (all->has_pipe)
		{
			dup2(all->fd[1], STDOUT_FILENO);
			close(all->fd[1]);
		}
		close(all->fd[0]);
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
		exit(1);
	}
	else
	{
		waitpid(all->child_pid, NULL, 0);
		close(all->fd[1]);
		all->tmp = all->fd[0];
	}
	return (0);
}



int	ft_execute(t_all *all, int *i, const char *in, const char *out)
{
	char	**token_str;

	//printf("===================================\n");
	token_str = ft_tokens_to_char(all, i);
	//ft_print_tokens(all);
	for (int x = 0; token_str[x]; x++)
	{
		printf("TOKEN[%d] : %s\n", x, token_str[x]);
	}
	if (token_str == NULL)
		return (1);
	if (pipe(all->fd) == -1)
	{
		perror("Pipe Error!");
		return (-1);
	}
	all->child_pid = fork();
	if (all->child_pid == -1)
	{
		perror("Fork Error!");
		return (-1);
	}
	all->has_pipe = ft_has_pipe_after(all, i);
	printf("PIPE ? : %d, in : %s, out : %s\n", all->has_pipe, in, out);
	ft_child_exec_pipe(in, out, token_str, all);
	/*if (all->child_pid == 0)
		ft_child_exec(in, out, token_str);
	else
		wait(NULL);*/
	//printf("\n TOKENS : %s\n", all->tokens[*i].value);
	if (all->tokens[*i].type == T_OUT || all->tokens[*i].type == T_OUT_APPEND)
		printf("--- OUT --- \n");
	return (-1);
}

char	*ft_get_out(t_all *all, int *i)
{
	int	j;

	j = *i;
	while (all->tokens[j].type == T_COMMAND || all->tokens[j].type == T_WORD || all->tokens[j].type == T_OUT)
	{
		printf("========> token[%d] : %s\n", j, all->tokens[j].value);
		j++;
	}
	printf("======================> token[%d] : %s\n", j, all->tokens[j].value);
	if (all->tokens[j].type == T_FILE_OUT)
		return (all->tokens[j].value);
	return (NULL);
}

int	ft_has_pipe_after(t_all *all, int *i)
{
	int	j;

	j = *i;
	while (all->tokens[j].type == T_COMMAND || all->tokens[j].type == T_FILE_OUT || all->tokens[j].type == T_OUT)
		j++;
	if (all->tokens[j].type == T_PIPE)
		return (1);
	return (0);
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
	ft_print_tokens(all);
	while (*i < len)
	{
		printf("IVELANY; i : %d, len : %d, type : %s\n", *i, len, ft_show_token(&tokens[*i]));
		if (tokens[*i].type == T_FILE_IN)
		{
			in = tokens[*i].value;
			printf("------------- in -------------, in : %s \n", in);
		}
		else if (tokens[*i].type == T_COMMAND)
		{
			out = ft_get_out(all, i);
			printf(">>>> in : %s, out : %s\n", in, out);
			ft_execute(all, i, in, out);
			in = NULL;
			out = NULL;
		}
		*i = *i + 1;
	}
	return (1);
}
