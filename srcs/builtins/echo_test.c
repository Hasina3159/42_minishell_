/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:22:37 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/12/06 10:22:38 by ntodisoa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char *remove_extra_spaces(char *str)
{
	char	*tmp;
	int		i;
	int		j;

	tmp = malloc(ft_strlen(str) + 1);
	if (!tmp)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		tmp[j] = str[i];
		if (str[i] == ' ')
		{
			while (str[i + 1] && str[i + 1] == ' ')
				i++;
		}
		i++;
		j++;
	}
	tmp[j] = '\0';
	free(str);
	str = ft_strdup(tmp);
	free(tmp);
	return (str);
}

char	*arg_in_quotes(char *str, t_all *all)
{
	char	*out;
	int		j;

	j = all->pos;
	out = NULL;
	while (j < all->token_count && !is_n_op(all->tokens[j].type))
	{
		if (all->tokens[j].value)
		{
			if (!ft_strncmp(all->tokens[j].value, str, ft_strlen(str) + 1))
			{
				if (all->tokens[j].second_type != T_STRING_D)
				{
					out = ft_strtrim(str, " ");
					out = remove_extra_spaces(out);
				}
				else
					out = ft_strdup(str);
				break ;
			}
		}
		j++;
	}
	return (out);
}

static char	*get_arg(char **av, int i, char *out, t_all *all)
{
	char	*tmp;
	char	*temp;

	temp = arg_in_quotes(av[i], all);
	if (!out)
	{
		if (!av[i + 1])
			out = ft_strdup(temp);
		else
			out = ft_strjoin(temp, " ");
		free(temp);
	}
	else
	{
		tmp = ft_strjoin(out, temp);
		free(out);
		if (!av[i + 1])
			out = ft_strdup(tmp);
		else
			out = ft_strjoin(tmp, " ");
		free(tmp);
		free(temp);
	}
	return (out);
}

char	*join_arg(char **av, int i, t_all *all)
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
		out = get_arg(av, i, out, all);
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

int	ft_echo(int argc, char **argv, t_all *all)
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
	to_print = join_arg(argv, i, all);
	if (to_print != NULL)
	{
		printf("%s", to_print);
		free(to_print);
	}
	if (nl)
		printf("\n");
	return (SUCCESS);
}
