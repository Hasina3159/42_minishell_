/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazafin <arazafin@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:00:50 by arazafin          #+#    #+#             */
/*   Updated: 2024/10/11 10:20:47 by arazafin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	ft_replace_hd(t_all *all, char *line)
{
	char	**vars;
	char	*value;
	int		i;
	char	*tmp;

	vars = ft_get_all_var(line);
	if (vars == NULL)
		return (0);
	i = 0;
	while (vars[i])
	{
		value = ft_getvarvalue(all, &vars[i][1]);
		tmp = ft_strdup(line);
		free(line);
		line = ft_str_repl_copy(tmp, vars[i], value);
		free(tmp);
		if (line)
			return (0);
		i++;
	}
	i = 0;
	free_split(vars);
	return (1);
}

void	hd_expand(t_all *all, char *line)
{
	while (!ft_replace_hd(all, line))
		continue ;
	expand_heredoc(all, line);
}
