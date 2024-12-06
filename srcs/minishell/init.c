/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:29:19 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/12/06 13:38:51 by ntodisoa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	init_sh_env(t_all *all)
{
	int			i;
	char		*key;
	char		*value;
	extern char	**environ;

	i = 0;
	if (!environ)
		return (1);
	while (environ[i])
	{
		key = ft_substr(environ[i], 0, ft_strchr(environ[i], '=') - environ[i]);
		value = ft_substr(environ[i], ft_strchr(environ[i], '=') \
				- environ[i] + 1, ft_strlen(environ[i]));
		ft_setvarvalue(all, key, value);
		i++;
	}
	key = ft_strdup("OLDPWD");
	value = ft_strdup(getenv("PWD"));
	ft_setvarvalue(all, key, value);
	return (0);
}

void	init_shell(t_all *all)
{
	int	i;

	all->env = NULL;
	if (init_sh_env(all))
	{
		print_error(NULL, NULL, "Error on creating environment variable");
		exit(1);
	}
	all->tmp = -1;
	all->exit_status = 0;
	all->sh = 0;
	all->cmd = NULL;
	all->hd_file = NULL;
	ft_sigint(0, NULL, all);
	setup_signal(SIGINT, CUSTOM);
	setup_signal(SIGQUIT, IGNORE);
	i = 0;
	while (i < TOKENS_MAX)
	{
		all->tokens[i].value = NULL;
		i++;
	}
}
