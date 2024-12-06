/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:25:00 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/12/06 14:19:10 by ntodisoa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void	hd_expand_exit(t_all *all, char *line, int i)
// {
// 	char	*tmp;
// 	char	*tmp2;
// 	char	*tmp3;
// 	char	*exit_status;

// 	tmp = ft_substr(line, 0, i);
// 	tmp2 = ft_substr(line, i + 2, ft_strlen(line) - i - 2);
// 	exit_status = ft_itoa(all->exit_status);
// 	tmp3 = ft_strjoin(tmp, exit_status);
// 	free(line);
// 	line = ft_strjoin(tmp3, tmp2);
// 	free(tmp);
// 	free(tmp2);
// 	free(tmp3);
// 	free(exit_status);
// }

// int	expand_heredoc(t_all *all, char *line)
// {
// 	int	i;

// 	i = 0;
// 	while (line[i])
// 	{
// 		if (line[i] == '$')
// 		{
// 			if (line[i + 1] == '?')
// 				hd_expand_exit(all, line, i);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

// int	ft_replace_hd(t_all *all, char *line)
// {
// 	char	**vars;
// 	char	*value;
// 	int		i;
// 	char	*tmp;

// 	vars = ft_get_all_var(line);
// 	if (vars == NULL)
// 		return (0);
// 	i = 0;
// 	while (vars[i])
// 	{
// 		value = ft_getvarvalue(all, &vars[i][1]);
// 		tmp = ft_strdup(line);
// 		free(line);
// 		line = ft_str_repl_copy(tmp, vars[i], value);
// 		free(tmp);
// 		if (line)
// 		{
// 			free_split(vars);
// 			return (0);
// 		}
// 		i++;
// 	}
// 	free_split(vars);
// 	return (1);
// }

// void	hd_expand(t_all *all, char *line)
// {
// 	while (!ft_replace_hd(all, line))
// 		continue ;
// 	expand_heredoc(all, line);
// }
void	append_char(char **str, char c)
{
	char	*tmp;
	int		len;

	if (!str || !*str)
		return ;
	len = ft_strlen(*str);
	tmp = malloc(len + 2);
	if (!tmp)
		return ;
	ft_strlcpy(tmp, *str, len + 1);
	tmp[len] = c;
	tmp[len + 1] = '\0';
	free(*str);
	*str = tmp;
}

void	append_char1(char **str, char c)
{
	char	*tmp;
	int		len;

	if (!str || !*str)
		return ;
	len = ft_strlen(*str);
	tmp = malloc(len + 2);
	if (!tmp)
		return ;
	ft_strlcpy(tmp, *str, len + 1);
	tmp[len] = c;
	tmp[len + 1] = '\0';
	free(*str);
	*str = tmp;
}

void	append_char2(char **str, char c)
{
	char	*tmp;
	int		len;

	if (!str || !*str)
		return ;
	len = ft_strlen(*str);
	tmp = malloc(len + 2);
	if (!tmp)
		return ;
	ft_strlcpy(tmp, *str, len + 1);
	tmp[len] = c;
	tmp[len + 1] = '\0';
	free(*str);
	*str = tmp;
}

void	append_char3(char **str, char c)
{
	char	*tmp;
	int		len;

	if (!str || !*str)
		return ;
	len = ft_strlen(*str);
	tmp = malloc(len + 2);
	if (!tmp)
		return ;
	ft_strlcpy(tmp, *str, len + 1);
	tmp[len] = c;
	tmp[len + 1] = '\0';
	free(*str);
	*str = tmp;
}

static void	expand_env_var(t_all *all, char *str, t_expand *exp)
{
	char	*key;
	char	*var_value;
	int		len;

	len = 1;
	while (str[exp->i + len] && (ft_isalnum(str[exp->i + len]) ||
			str[exp->i + len] == '_'))
		len++;
	key = ft_substr(str, exp->i + 1, len - 1);
	var_value = get_env_value(all->env, key);
	if (var_value)
		exp->result = ft_strjoin_free(exp->result, var_value);
	free(key);
	exp->i += len - 1;
}

static void	expand_exit_status(t_all *all, t_expand *exp)
{
	char	*exit_status;

	exit_status = ft_itoa(all->exit_status);
	exp->result = ft_strjoin_free(exp->result, exit_status);
	free(exit_status);
	exp->i++;
}

static void	handle_dollar(t_all *all, char *str, t_expand *exp)
{
	if (str[exp->i + 1] == '?')
		expand_exit_status(all, exp);
	else if (ft_isalpha(str[exp->i + 1]) || str[exp->i + 1] == '_')
		expand_env_var(all, str, exp);
	else if (ft_strlen(str) == 1)
		append_char1(&exp->result, str[exp->i]);
	else
		exp->i++;
}

char	*hd_expand(t_all *all, char *line)
{
	t_expand exp;

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
