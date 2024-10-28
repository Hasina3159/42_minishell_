/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazafin <arazafin@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:00:45 by arazafin          #+#    #+#             */
/*   Updated: 2024/10/11 10:22:35 by arazafin         ###   ########.fr       */
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
	if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
	{
		free(line);
		return (1);
	}
	return (0);
}

void	here_doc(t_token lim, int fd_out, t_all *all)
{
	char	*line;
	char	*doc;
	int		expand;

	doc = NULL;
	expand = 1;
	if (lim.second_type == T_STRING_D || lim.second_type == T_STRING_S)
		expand = 0;
	while (1)
	{
		line = readline("heredoc> ");
		if (hd_signal(line, lim.value))
			break ;
		if (is_limiter(lim.value, line))
			break ;
		if (expand)
			hd_expand(all, line);
		doc = get_heredoc(doc, line);
		free(line);
	}
	if (!doc)
		doc = ft_strdup("");
	ft_putstr_fd(doc, fd_out);
	free(doc);
}

void	heredoc(t_all *all, t_token lim)
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
	here_doc(lim, tmp_fd, all);
	close(tmp_fd);
}
