/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_all_dir_operations_1.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazafin <arazafin@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 08:12:46 by arazafin          #+#    #+#             */
/*   Updated: 2024/10/08 08:47:54 by arazafin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_show_all_dirs(t_dir **dirs)
{
	t_dir	*tmp;

	printf("------------------- ALL DIRS -------------------\n");
	tmp = *dirs;
	while (tmp)
	{
		usleep(5000);
		printf("> start : %p - end : %p, FILE : %s > TYPE : ", tmp,
			tmp + sizeof(tmp), tmp->name);
		if (tmp->type == FILE_DIR)
			printf("_DIRECTORY_\n");
		else
			printf("_FILE_\n");
		tmp = tmp->next;
	}
	printf("------------------------------------------------\n");
}

t_dir	**ft_init_dirs(void)
{
	t_dir	**dir;

	dir = ft_calloc(1, sizeof(t_dir **));
	if (dir == NULL)
		return (NULL);
	return (dir);
}
