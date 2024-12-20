/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:23:08 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/12/20 09:40:31 by ntodisoa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_pwd(t_all *all)
{
	char	pwd[TOKENS_MAX];
	int		error;

	(void)all;
	if (getcwd(pwd, TOKENS_MAX) == NULL)
	{
		error = errno;
		print_error("pwd", NULL, strerror(error));
		return (ERROR);
	}
	printf("%s\n", pwd);
	return (SUCCESS);
}
