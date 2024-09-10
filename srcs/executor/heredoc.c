#include "../../include/minishell.h"

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

static int	get_key_sublen(int i, char *line)
{
	int		len;

	len = i + 1;
	while (ft_isalnum(line[len]) || line[len] == '_')
		len++;
	return (len);
}

static char	*new_value(char *before, char *env, char *after)
{
	char	*out;
	char	*tmp;

	if (before[0] == '\0' || before == NULL)
	{
		if (!env)
			tmp = ft_strdup("");
		else
			tmp = ft_strdup(env);
	}
	else if (!env)
		tmp = ft_strdup(before);
	else
		tmp = ft_strjoin(before,env);
	out = ft_strjoin(tmp, after);
	free(tmp);
	return (out);
}

void	hd_expand_env(t_env *env, char *line, int i)
{
	char	*before;
	char	*after;
	char	*key;
	t_env	*tmp_env;

	tmp_env = env;
	key = ft_substr(line, i + 1, get_key_sublen(i, line));
	before = ft_substr(line, 0, i);
	after = ft_substr(line, get_key_sublen(i, line), ft_strlen(line));
	while (tmp_env)
	{
		if (!ft_strncmp(tmp_env->key, key, ft_strlen(key) - 1))
			break ;
		tmp_env = tmp_env->next;
	}
	free(line);
	if (tmp_env != NULL)
		line = new_value(before, tmp_env->value, after);
	else
		line = new_value(before, NULL, after);
	free(key);
	free(before);
	free(after);
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
			else if (ft_isalpha(line[i + 1]))
				hd_expand_env(all->env, line, i);
			i = 0;
			continue ;
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
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			free(line);
			break ;
		}
		doc = get_heredoc(doc, line);
		free(line);
	}
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
	all->hd_file = ft_strjoin(tmp, ".heredoc"); // TODO: free hd_file
	free(tmp);
	tmp_fd = open(all->hd_file, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (tmp_fd == -1)
	{
		perror("open");
		return ;
	}
	here_doc(limiter, tmp_fd, all);
	close(tmp_fd);
	// TODO: n'oublie pas de supprimer hd_file apres redirection
	// ? unlink(".heredoc");
}
