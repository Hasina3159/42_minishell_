#include "../minishell.h"

int ft_replace_var(t_all *all, t_token *token)
{
	char	**vars;
	char	*value;
	int		i;

	vars = ft_get_all_var(token->value);
	if (vars == NULL)
		return (0);
	ft_show_all_var(vars);

	i = 0;
	while (vars[i])
	{
		value = ft_getvarvalue(all, &vars[i][1]);
		if (!ft_str_repl(token->value, vars[i], value))
			return (0);
		i++;
	}
	i = 0;
	while (vars[i])
	{
		if (vars[i])
			free(vars[i]);
		i++;
	}
	if (vars)
		free(vars);
	return (1);
}

int	ft_replace_all_vars(t_all *all)
{
	t_token	*token;
	int		i;

	i = 0;
	token = all->tokens;
	while (i < all->token_count)
	{
		if (token[i].type != T_STRING_S && !ft_replace_var(all, &token[i]))
			return (0);
		i++;
	}
	return (1);
}