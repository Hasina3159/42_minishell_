/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hd_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:24:27 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/12/20 09:40:38 by ntodisoa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	hd_lim_sig(char *line, t_token lim)
{
	if (hd_signal(line, lim.value))
		return (1);
	if (is_limiter(lim.value, line))
		return (1);
	return (0);
}

static void	expand_tok_hd(char **line, t_all *all)
{
	char	*expanded;

	expanded = hd_expand(all, *line);
	if (expanded)
	{
		free(*line);
		*line = expanded;
	}
}

int	hd_loop(t_all *all, t_token lim, char **doc, int fd_out)
{
	char	*in_std;
	char	*line;

	in_std = ttyname(STDIN_FILENO);
	while (1)
	{
		all->second = 1;
		line = readline("heredoc> ");
		if (all->exit_status == 130)
		{
			new_std(in_std);
			free(line);
			free(*doc);
			close(fd_out);
			all->second = 0;
			return (1);
		}
		if (hd_lim_sig(line, lim))
			break ;
		if (all->hd_expand)
			expand_tok_hd(&line, all);
		*doc = get_heredoc(*doc, line);
		free(line);
	}
	return (0);
}

int	here_doc(t_token lim, int fd_out, t_all *all)
{
	char	*doc;

	doc = NULL;
	all->hd_expand = 1;
	all->second = 1;
	if (lim.second_type == T_STRING_D || lim.second_type == T_STRING_S)
		all->hd_expand = 0;
	if (hd_loop(all, lim, &doc, fd_out))
		return (1);
	if (!doc)
		doc = ft_strdup("");
	ft_putstr_fd(doc, fd_out);
	free(doc);
	return (0);
}
