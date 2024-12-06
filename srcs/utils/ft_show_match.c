/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_show_match.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:35:38 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/12/06 10:35:39 by ntodisoa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_show_match(t_dir **dirs)
{
	t_dir	*tmp;

	tmp = *dirs;
	while (tmp)
	{
		if (ft_match(tmp->name, "*/*"))
			printf("%s\n", tmp->name);
		tmp = tmp->next;
	}
}

char	*ft_get_wildcard(t_dir **dirs, char *w)
{
	char	*final;
	t_dir	*tmp;
	int		i;

	tmp = *dirs;
	final = ft_strdup("");
	i = 0;
	while (tmp)
	{
		if (ft_match(tmp->name, w))
		{
			if (i != 0)
				final = better_strjoin(final, " ");
			final = better_strjoin(final, tmp->name);
		}
		i++;
		tmp = tmp->next;
	}
	return (final);
}
