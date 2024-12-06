/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 14:34:02 by arazafin          #+#    #+#             */
/*   Updated: 2024/12/06 13:26:44 by ntodisoa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*get_arg(char **av, int i, char *out)
{
	char	*tmp;

	if (!out)
	{
		if (!av[i + 1])
			out = ft_strdup(av[i]);
		else
			out = ft_strjoin(av[i], " ");
	}
	else
	{
		tmp = ft_strjoin(out, av[i]);
		free(out);
		out = NULL;
		if (!av[i + 1])
			out = ft_strdup(tmp);
		else
			out = ft_strjoin(tmp, " ");
		free(tmp);
		tmp = NULL;
	}
	return (out);
}

char	*join_arg(char **av, int i)
{
	char	*out;

	out = NULL;
	while (av[i])
	{
		if (av[i] == NULL)
		{
			i++;
			continue ;
		}
		out = get_arg(av, i, out);
		i++;
	}
	return (out);
}

int	check_flag(char **av, int *i)
{
	int	j;

	while (av[*i] && !ft_strncmp(av[*i], "-n", 2))
	{
		j = 2;
		while (av[*i][j] == 'n')
			j++;
		if (av[*i][j] != '\0')
			break ;
		(*i)++;
	}
	if (*i > 1)
		return (0);
	return (1);
}

int	ft_echo(int argc, char **argv)
{
	int		nl;
	int		i;
	char	*to_print;

	if (argc == 1)
	{
		printf("\n");
		return (SUCCESS);
	}
	i = 1;
	nl = check_flag(argv, &i);
	to_print = join_arg(argv, i);
	if (to_print != NULL)
	{
		printf("%s", to_print);
		free(to_print);
	}
	if (nl)
		printf("\n");
	return (SUCCESS);
}
