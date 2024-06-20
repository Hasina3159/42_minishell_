/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:43:48 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/02/21 12:48:30 by ntodisoa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_clear(t_list *list, void (*del)(void *))
{
	if (list->next)
		ft_clear(list->next, del);
	del(list->content);
	free(list);
}

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	ft_clear(lst[0], del);
	lst[0] = NULL;
}
