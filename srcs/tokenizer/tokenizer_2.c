/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazafin <arazafin@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 09:31:06 by arazafin          #+#    #+#             */
/*   Updated: 2024/10/08 09:32:05 by arazafin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_is_var(char *s)
{
	if (*s != '$')
		return (0);
	if (s[1] && (ft_isalpha(s[1]) || s[1] == '_'))
		return (1);
	return (0);
}

int	ft_count_var(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (ft_is_var(&s[i]))
			count++;
		i++;
	}
	return (count);
}

char	*ft_extract_var(char *s)
{
	int		len;
	char	*final;

	if (!ft_is_var(s))
		return (NULL);
	len = 1;
	while (s[len] && ft_is_varchar(s[len]))
		len++;
	if (len == 0)
		return (NULL);
	final = ft_strndup(s, len);
	if (final == NULL)
		return (NULL);
	return (final);
}

char	**ft_get_all_var(char *s)
{
	char	**all_var;
	int		i;
	int		j;
	int		len;
	char	*var;

	len = ft_count_var(s);
	all_var = (char **)malloc(sizeof(char *) * (len + 1));
	if (all_var == NULL)
		return (NULL);
	all_var[len] = NULL;
	i = 0;
	j = 0;
	while (s[i])
	{
		var = ft_extract_var(&s[i]);
		if (var)
		{
			all_var[j] = var;
			j++;
		}
		i++;
	}
	return (all_var);
}

void	ft_show_all_var(char **var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		printf("> Var[%d] : %s\n", i, var[i]);
		i++;
	}
}
