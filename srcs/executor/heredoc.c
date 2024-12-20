/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:25:06 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/12/20 09:40:42 by ntodisoa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	hd_signal(char *line, char *limiter)
{
	if (!line)
	{
		print_error("warning", "terminate here_doc without", limiter);
		return (1);
	}
	return (0);
}

int	is_limiter(char *limiter, char *line)
{
	if (ft_strncmp(line, limiter, ft_strlen(line) + 1) == 0)
	{
		free(line);
		return (1);
	}
	return (0);
}

int	heredoc(t_all *all, t_token lim)
{
	int		tmp_fd;
	char	*tmp;

	tmp = getcwd(NULL, 0);
	if (tmp == NULL)
	{
		perror("getcwd");
		return (1);
	}
	all->hd_file = ft_strjoin(tmp, "/.heredoc");
	free(tmp);
	tmp_fd = open(all->hd_file, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (tmp_fd == -1)
	{
		perror("open");
		return (1);
	}
	if (here_doc(lim, tmp_fd, all))
		return (2);
	close(tmp_fd);
	return (0);
}
