/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_utils_0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 14:20:44 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/12/08 14:32:18 by ntodisoa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

void	expand_env_var_1(t_all *all, char *str, t_expand *exp)
{
	char	*key;
	char	*var_value;
	int		len;

	len = 1;
	while (str[exp->i + len] && (ft_isalnum(str[exp->i + len]) || \
			str[exp->i + len] == '_'))
		len++;
	key = ft_substr(str, exp->i + 1, len - 1);
	var_value = get_env_value(all->env, key);
	if (var_value)
		exp->result = ft_strjoin_free(exp->result, var_value);
	free(key);
	exp->i += len - 1;
}
