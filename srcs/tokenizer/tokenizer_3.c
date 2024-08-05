#include "../minishell.h"

int	ft_replace_var(t_all *all, t_token *token)
{
	char	**vars;
	char	*value;
	int		i;
	(void) all;
	vars = ft_get_all_var(token->value);
	if (vars == NULL)
		return (0);
	ft_show_all_var(vars);
	i = 0;
	while (vars[i])
	{
		value = ft_getvarvalue(all, &vars[i][1]);
		//printf("VARS : %s\n", vars[i]);
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

void	ft_finalize_token(t_all *all)
{
	t_token	*tokens;
	t_token	*now;
	t_token	*prec;
	int		i;

	i = 0;
	tokens = all->tokens;
	while (i < all->token_count)
	{
		if (i != 0)
			prec = &tokens[i - 1];
		else
			prec = NULL;
		now = &tokens[i];
		if (prec && (prec->type == T_FILE_OUT || prec->type == T_FILE_IN) && now->type == T_WORD)
			now->type = T_COMMAND;
		i++;
	}
}
