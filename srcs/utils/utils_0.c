#include "../minishell.h"

int	ft_is_separator(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

int	ft_is_quotes(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}

void	ft_pass_separator(char const *s, int *i, int *count, int *is_in_a_str)
{
	while (s[*i] && (ft_is_separator(s[*i]) || s[*i] == ' ')
		&& !ft_is_quotes(s[*i]) && !*is_in_a_str)
	{
		if (ft_is_separator(s[*i]))
			*count = *count + 1;
		*i = *i + 1;
	}
}

void	ft_pass_quotes(char const *s, int *i, int *count, int *is_in_a_str)
{
	int	flag;
	int	is_count_inc;

	flag = 0;
	is_count_inc = 0;
	if (s[*i] && ft_is_quotes(s[*i]))
	{
		if (*is_in_a_str)
			*is_in_a_str = 0;
		else
			*is_in_a_str = s[*i];
		*i = *i + 1;
	}
	if (*is_in_a_str)
	{
		while (*is_in_a_str)
		{
			flag = 1;
			if (s[*i] && s[*i] == *is_in_a_str)
			{
				*is_in_a_str = 0;
				*i = *i + 1;
				if (*count == 0)
				{
					is_count_inc = 1;
					*count = *count + 1;
				}
			}
			*i = *i + 1;
		}
	}
	if (!is_count_inc && flag == 1)
		*count = *count + 1;
}

int	ft_count_words(char const *s)
{
	int	i;
	int	count;
	int	is_in_a_str;
	int	inc_count;

	i = 0;
	count = 0;
	is_in_a_str = 0;
	while (s[i])
	{
		ft_pass_separator(s, &i, &count, &is_in_a_str);
		ft_pass_quotes(s, &i, &count, &is_in_a_str);
		inc_count = 0;
		while (s[i] && !ft_is_separator(s[i]) && s[i] != ' '
			&& !ft_is_quotes(s[i]) && !is_in_a_str)
		{
			inc_count = 1;
			i++;
			printf("-");
		}
		if (inc_count)
			count++;
	}
	return (count);
}
