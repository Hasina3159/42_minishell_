/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:27:38 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/12/06 15:27:56 by ntodisoa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
