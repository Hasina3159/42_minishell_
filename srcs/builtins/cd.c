/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:22:31 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/12/06 13:27:44 by ntodisoa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	update_pwd_env(t_all *all, char *oldpwd)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	ft_setvarvalue(all, ft_strdup("PWD"), pwd);
	ft_setvarvalue(all, ft_strdup("OLDPWD"), oldpwd);
}

int	expand_cd_arg(char **av, t_all *all)
{
	t_env	*tmp;

	tmp = all->env;
	if (!ft_strncmp(av[1], "-", 2))
	{
		if (!ft_search_key("OLDPWD", all))
		{
			print_error("cd", NULL, "OLDPWD not set");
			return (1);
		}
		free(av[1]);
		av[1] = NULL;
		while (tmp)
		{
			if (!ft_strncmp(tmp->key, "OLDPWD", 6))
				break ;
			tmp = tmp->next;
		}
		av[1] = ft_strdup(tmp->value);
		printf("%s\n", av[1]);
	}
	return (0);
}

static int	cd_case_one(t_all *all, char *oldpwd)
{
	char	*dir;

	dir = NULL;
	if (ft_search_key("HOME", all))
	{
		dir = ft_get_env("HOME", all);
		if (dir)
			chdir(dir);
		else
		{
			print_error("cd", NULL, "HOME not set");
			free(oldpwd);
			oldpwd = NULL;
			return (1);
		}
	}
	else
	{
		print_error("cd", NULL, "HOME not set");
		free(oldpwd);
		oldpwd = NULL;
		return (1);
	}
	return (0);
}

static int	cd_case_two(char **av, t_all *all, char *oldpwd)
{
	int		error;

	if (!expand_cd_arg(av, all))
	{
		if (chdir(av[1]) == -1)
		{
			error = errno;
			print_error("cd", av[1], strerror(error));
			free(oldpwd);
			oldpwd = NULL;
			return (1);
		}
	}
	else
	{
		free(oldpwd);
		oldpwd = NULL;
		return (1);
	}
	return (0);
}

int	ft_cd(char **av, t_all *all)
{
	int		ac;
	char	*oldpwd;

	ac = ft_count_splitted(av);
	if (ac > 2)
	{
		print_error("cd", NULL, "too much argument");
		return (ERROR);
	}
	oldpwd = getcwd(NULL, 0);
	if (ac == 1)
	{
		if (cd_case_one(all, oldpwd))
			return (ERROR);
	}
	else
	{
		if (cd_case_two(av, all, oldpwd))
			return (ERROR);
	}
	update_pwd_env(all, oldpwd);
	return (SUCCESS);
}
