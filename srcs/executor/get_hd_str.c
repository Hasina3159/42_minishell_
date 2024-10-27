/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hd_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazafin <arazafin@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:05:14 by arazafin          #+#    #+#             */
/*   Updated: 2024/10/25 13:27:41 by arazafin         ###   ########.fr       */
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
			hd_expand(all, line);
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
