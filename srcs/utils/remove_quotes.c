/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:36:37 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/12/06 10:36:38 by ntodisoa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_remove_quotes(char *s)
{
	char	*new_string;
	size_t	len;

	new_string = NULL;
	if (s == NULL)
		return (NULL);
	if (*s == 0)
		return (ft_strdup(""));
	len = ft_strlen(s);
	if (!ft_strncmp(s, "''", len) || !ft_strncmp(s, "\"\"", len))
		return (ft_strdup(""));
	if ((*s == '\'' && s[len - 1] == '\'') || (*s == '"' && s[len - 1] == '"'))
	{
		len = len - 2;
		new_string = ft_strndup(&(s[1]), len);
		return (new_string);
	}
	return (ft_strdup(s));
}
