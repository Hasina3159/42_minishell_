/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazafin <arazafin@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 14:35:00 by arazafin          #+#    #+#             */
/*   Updated: 2024/09/29 14:35:09 by arazafin         ###   ########.fr       */
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
		print_error("cd", NULL, strerror(error));
		return (ERROR);
	}
	printf("%s\n", pwd);
	return (SUCCESS);
}
