/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:44:02 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/02/23 15:42:14 by ntodisoa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	**new_list;
	t_list	*nw;
	void	*content;

	new_list = (t_list **)malloc(sizeof(t_list *));
	if (new_list == NULL)
		return (NULL);
	while (lst)
	{
		content = f(lst->content);
		nw = ft_lstnew(content);
		del(nw->content);
		ft_lstadd_back(new_list, nw);
		lst = lst->next;
	}
	return (*new_list);
}
