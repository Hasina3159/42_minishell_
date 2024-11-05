/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_all_dir_operations_0.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazafin <arazafin@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 08:12:13 by arazafin          #+#    #+#             */
/*   Updated: 2024/11/05 08:57:06 by arazafin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_opendir(char *path, DIR **dir)
{
	*dir = opendir(path);
	if (dir == NULL)
	{
		perror("opendir");
		exit(EXIT_FAILURE);
	}
}

void	ft_closedir(DIR **dir)
{
	if (closedir(*dir) == -1)
	{
		perror("closedir");
		exit(EXIT_FAILURE);
	}
}

int	ft_isdir(char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) == -1)
	{
		// perror("stat");
		// printf("%d\n", errno);
		return (-1);
	}
	if ((statbuf.st_mode & S_IFMT) == S_IFDIR)
		return (1);
	return (0);
}

t_dir	*ft_create_dir(char *name, int type)
{
	t_dir	*dir;

	dir = (t_dir *)malloc(sizeof(t_dir));
	if (dir == NULL)
		return (NULL);
	dir->name = name;
	dir->type = type;
	dir->next = NULL;
	return (dir);
}

void	ft_add_dir(t_dir **lst, t_dir *elem)
{
	t_dir	*tmp;

	if (*lst == NULL)
	{
		*lst = elem;
		return ;
	}
	tmp = *lst;
	while (tmp && tmp->next)
	{
		tmp = tmp->next;
	}
	if (tmp && tmp != elem)
		tmp->next = elem;
}
