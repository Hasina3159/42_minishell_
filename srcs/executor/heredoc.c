#include "../../include/minishell.h"

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

void	here_doc(char *limiter, int fd_out)
{
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

void	heredoc(char *limiter)
{
	int	tmp_fd;

	tmp_fd = open(".heredoc", O_CREAT | O_RDWR | O_APPEND, 0777);
	here_doc(limiter, tmp_fd);
	// code here //
	close(tmp_fd);
	unlink(".heredoc");
}
