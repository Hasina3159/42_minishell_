/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:23:01 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/12/20 09:40:29 by ntodisoa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_exported(t_all *all)
{
	t_env	*tmp;

	tmp = all->env;
	while (tmp)
	{
		printf("declare -x %s", tmp->key);
		if (tmp->value != NULL)
			printf("=\"%s\"", tmp->value);
		printf("\n");
		tmp = tmp->next;
	}
}

int	is_valid_arg(char *arg)
{
	int	i;

	i = 0;
	if (!ft_isalpha(arg[i]) && arg[i] != '_')
		return (0);
	++i;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		++i;
	}
	return (1);
}

void	add_export_variable(t_all *all, char *arg)
{
	char	*key;
	char	*value;

	if (ft_strchr(arg, '=') != NULL)
	{
		key = ft_substr(arg, 0, ft_strchr(arg, '=') - arg);
		value = ft_substr(arg, ft_strchr(arg, '=') - arg + 1, ft_strlen(arg));
	}
	else
	{
		key = ft_strdup(arg);
		value = NULL;
	}
	ft_setvarvalue(all, key, value);
}

int	ft_export(t_all *all, char **av)
{
	int	i;
	int	ac;

	ac = ft_count_splitted(av);
	if (ac < 2)
	{
		print_exported(all);
		return (0);
	}
	i = 1;
	while (av[i])
	{
		if (is_valid_arg(av[i]))
			add_export_variable(all, av[i]);
		else
			print_error(av[0], av[i], "is not a valid identifier");
		i++;
	}
	return (0);
}
