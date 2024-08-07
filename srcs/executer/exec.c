#include "../minishell.h"

char	**ft_tokens_to_char(t_all *all, int *i)
{
	char	**token_str;
	int		len;
	int		old_i;
	int		j;

	len = 0;
	old_i = *i;
	while ((len + *i) < all->token_count && (all->tokens[len + *i].type == T_COMMAND || all->tokens[len + *i].type == T_WORD))
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

int	ft_dup_stdin(const char *in)
{
	int	fd_in;

	if (in == NULL)
		return (0);
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
	fd_out = open("/dev/null", O_WRONLY | O_CREAT | O_TRUNC, 0644);
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
	int			i;

	if (all->child_pid == 0)
	{
		if (all->tmp != -1)
		{
			if (dup2(all->tmp, STDIN_FILENO) == -1)
			{
				perror("dup2 tmp to stdin");
				exit(1);
			}
			close(all->tmp);
		}
		if (all->has_pipe)
		{
			if (dup2(all->fd[1], STDOUT_FILENO) == -1)
			{
				perror("dup2 fd[1] to stdout");
				exit(1);
			}
			close(all->fd[1]);
		}
		close(all->fd[0]);
		if (!ft_strncmp(token_str[0], "tee", 3) && !ft_has_pipe_after(all, &all->x))
		{
			ft_dup_stdout("test");
			printf("=======================> OUT : %s, t[0] : %s\n", out, token_str[0]);
			i = 0;
			while (token_str[i])
			{
				printf("==> Token[%d] : %s\n", i, token_str[i]);
				i++;
			}
		}
		i = 0;
		while (token_str[i])
		{
			printf("Token[%d] : %s\n", i, token_str[i]);
			i++;
		}
		if (in)
			token_str[i] = ft_strdup(in);
		if (token_str[0])
			execve(token_str[0], token_str, environ);
		cmd_with_path = ft_strjoin("/bin/", token_str[0]);
		if (cmd_with_path)
		{
			execve(cmd_with_path, token_str, environ);
			free(cmd_with_path);
		}
		cmd_with_path = ft_strjoin("/usr/bin/", token_str[0]);
		if (cmd_with_path)
		{
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

	token_str = ft_tokens_to_char(all, i);
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
	all->x = *i;
	ft_child_exec_pipe(in, out, token_str, all);
	return (0);
}

char	*ft_get_out(t_all *all, int *i)
{
	int	j;
	int	has_pipe;
	int	has_tee;

	j = *i;
	has_pipe = 0;
	has_tee = 0;
	while (all->tokens[j].type == T_COMMAND || all->tokens[j].type == T_WORD || all->tokens[j].type == T_OUT)
		j++;
	if (all->tokens[j].type == T_PIPE)
		j++;
	printf("TEE ? : %s\n", all->tokens[j].value);
	if (!ft_strncmp(all->tokens[j].value, "tee", 4))
		has_tee = 1;
	while (all->tokens[j].type == T_COMMAND || all->tokens[j].type == T_WORD || all->tokens[j].type == T_OUT)
		j++;
	if (all->tokens[j].type == T_PIPE)
		has_pipe = 1;
	printf("TEE : %d, PIPE : %d\n", has_tee, has_pipe);
	if (has_tee && !has_pipe)
	{
		printf(">>> TEE : %d, PIPE : %d\n", has_tee, has_pipe);
		return (all->tokens[j].value);
	}
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
	t_token	*tokens;
	int		len;
	char	*in;
	char	*out;

	ft_print_tokens(all);
	len = all->token_count;
	tokens = all->tokens;
	in = NULL;
	out = NULL;
	while (*i < len)
	{
		if (tokens[*i].type == T_FILE_IN)
		{
			in = tokens[*i].value;
		}
		else if (tokens[*i].type == T_COMMAND)
		{
			out = ft_get_out(all, i);
			ft_execute(all, i, in, out);
			in = NULL;
			out = NULL;
		}
		*i = *i + 1;
	}
	return (1);
}
