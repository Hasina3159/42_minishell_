/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:28:43 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/12/06 10:28:44 by ntodisoa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	append_char(char **str, char c)
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
	else if (ft_strlen(str) == 1 && is_n_op(all->tokens[exp->tok_i + 1].type))
		append_char(&exp->result, str[exp->i]);
	else
		exp->i++;
}

char	*expand_variables(t_all *all, char *str, int i)
{
	t_expand exp;

	if (!str)
		return (NULL);
	exp.result = ft_strdup("");
	exp.i = 0;
	exp.tok_i = i;
	while (str[exp.i])
	{
		if (str[exp.i] == '$')
			handle_dollar(all, str, &exp);
		else
			append_char(&exp.result, str[exp.i]);
		if (!str[exp.i])
			break ;
		exp.i++;
	}
	return (exp.result);
}
