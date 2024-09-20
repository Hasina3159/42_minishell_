#include "../../include/minishell.h"

/*static int	replace_var(t_all *all, char *str)
{
	char	**vars;
	char	*value;
	int		i;
	char	*tmp;

	(void) all;
	vars = ft_get_all_var(str);
	if (vars == NULL)
		return (0);
	i = 0;
	while (vars[i])
	{
		value = ft_getvarvalue(all, &vars[i][1]);
		tmp = ft_strdup(str);
		free(str);
		str = ft_str_repl_copy(tmp, vars[i], value);
		free(tmp);
		if (str)
			return (0);
		i++;
	}
	i = 0;
	while (vars[i])
	{
		if (vars[i])
			free(vars[i]);
		i++;
	}
	if (vars)
		free(vars);
	return (1);
}

static int	replace_all_vars(t_all *all)
{
	t_token	*token;
	int		i;

	i = 0;
	token = all->tokens;
	while (i < all->token_count)
	{
		if (token[i].type != T_STRING_S && !ft_replace_var(all, &token[i]))
			return (0);
		i++;
	}
	return (1);
}*/

void	hd_expand_exit(t_all *all, char *line, int i)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	char	*exit_status;

	tmp = ft_substr(line, 0, i);
	tmp2 = ft_substr(line, i + 2, ft_strlen(line) - i - 2);
	exit_status = ft_itoa(all->exit_status);
	tmp3 = ft_strjoin(tmp, exit_status);
	free(line);
	line = ft_strjoin(tmp3, tmp2);
	free(tmp);
	free(tmp2);
	free(tmp3);
	free(exit_status);
}

int	expand_heredoc(t_all *all, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			if (line[i + 1] == '?')
				hd_expand_exit(all, line, i);
		}
		i++;
	}
	return (0);
}

char	*get_heredoc(char *doc, char *line)
{
	char	*tmp;

	if (doc == NULL)
		doc = ft_strjoin(line, "\n");
	else
	{
		tmp = ft_strjoin(doc, line);
		free(doc);
		doc = ft_strjoin(tmp, "\n");
		free(tmp);
	}
	return (doc);
}

void	here_doc(char *limiter, int fd_out, t_all *all)
{
	(void)all;
	char	*line;
	char	*doc;

	doc = NULL;
	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
		{
			print_error("warning", "terminate here_doc without", limiter);
			break ;
		}
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			free(line);
			break ;
		}
		// expand_heredoc(all, line);
		doc = get_heredoc(doc, line);
		free(line);
	}
	if (!doc)
		doc = ft_strdup("");
	ft_putstr_fd(doc, fd_out);
	free(doc);
}

void	heredoc(t_all *all, char *limiter)
{
	int		tmp_fd;
	char	*tmp;

	tmp = getcwd(NULL, 0);
	if (tmp == NULL)
	{
		perror("getcwd");
		return ;
	}
	all->hd_file = ft_strjoin(tmp, "/.heredoc");
	free(tmp);
	tmp_fd = open(all->hd_file, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (tmp_fd == -1)
	{
		perror("open");
		return ;
	}
	here_doc(limiter, tmp_fd, all);
	close(tmp_fd);
}
