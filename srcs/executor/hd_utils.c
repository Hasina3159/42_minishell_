/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:25:00 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/12/20 09:40:41 by ntodisoa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	expand_exit_status(t_all *all, t_expand *exp)
{
	char	*exit_status;

	exit_status = ft_itoa(all->exit_status);
	exp->result = ft_strjoin_free(exp->result, exit_status);
	free(exit_status);
	exp->i++;
}

void	handle_dollar(t_all *all, char *str, t_expand *exp)
{
	if (str[exp->i + 1] == '?')
		expand_exit_status(all, exp);
	else if (ft_isalpha(str[exp->i + 1]) || str[exp->i + 1] == '_')
		expand_env_var_1(all, str, exp);
	else if (ft_strlen(str) == 1)
		append_char1(&exp->result, str[exp->i]);
	else
		exp->i++;
}

char	*hd_expand(t_all *all, char *line)
{
	t_expand	exp;

	if (!line)
		return (NULL);
	exp.result = ft_strdup("");
	exp.i = 0;
	while (line[exp.i])
	{
		if (line[exp.i] == '$')
			handle_dollar(all, line, &exp);
		else
			append_char(&exp.result, line[exp.i]);
		exp.i++;
	}
	return (exp.result);
}

int	ft_isdir(char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) == -1)
		return (-1);
	if ((statbuf.st_mode & S_IFMT) == S_IFDIR)
		return (1);
	return (0);
}
