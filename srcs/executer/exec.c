#include "../minishell.h"

char	**ft_tokens_to_char(t_all *all, int *i)
{
	char	**token_str;
	int		len;

	len = 0;
	while (len < all->token_count && (all->tokens[len].type == T_COMMAND
			|| all->tokens[len].type == T_WORD))
		len++;
	printf("\n\nLen : %d\n", len);
	token_str = (char **)ft_calloc(len + 1, sizeof(char *));
	if (token_str == NULL)
		return (NULL);
	while (*i < len)
	{
		token_str[*i] = ft_strdup(all->tokens[*i].value);
		printf("Token : %s\n", token_str[*i]);
		*i = *i + 1;
	}
	return (token_str);
}

int	ft_child_exec(const char *in, const char *out, char **token_str)
{
	int			fd_in;
	int			fd_out;
	extern char	**environ;
	char		*cmd_with_path;

	fd_in = open(in, O_RDONLY);
	if (fd_in == -1)
	{
		perror("open input");
		return (1);
	}
	if (dup2(fd_in, STDIN_FILENO) == -1)
	{
		perror("dup2 input");
		close(fd_in);
		return (1);
	}
	close(fd_in);
	fd_out = open(out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
	{
		perror("open output");
		return (1);
	}
	if (dup2(fd_out, STDOUT_FILENO) == -1)
	{
		perror("dup2 output");
		close(fd_out);
		return (1);
	}
	close(fd_out);
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

int	ft_execute(t_all *all, int *i)
{
	char	**token_str;
	int		pid;
	int		fd[2];

	token_str = ft_tokens_to_char(all, i);
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
		ft_child_exec("Makefile", "test", token_str);
	}
	else
		wait(NULL);
	printf("\n TOKENS : %s\n", all->tokens[*i].value);
	if (all->tokens[*i].type == T_OUT || all->tokens[*i].type == T_OUT_APPEND)
		printf("--- OUT --- \n");
	return (-1);
}
