#include "../minishell.h"

void	ft_set_operator(t_token *token)
{
	int	len;

	len = ft_strlen(token->value);
	if (!ft_strncmp(token->value, "|", len))
		token->type = T_PIPE;
	else if (!ft_strncmp(token->value, "||", len))
		token->type = T_OR;
	else if (!ft_strncmp(token->value, "&&", len))
		token->type = T_AND;
	else if (!ft_strncmp(token->value, "(", len))
		token->type = T_P_OPEN;
	else if (!ft_strncmp(token->value, ")", len))
		token->type = T_P_CLOSE;
	else if (!ft_strncmp(token->value, "<", len))
		token->type = T_IN;
	else if (!ft_strncmp(token->value, ">", len))
		token->type = T_OUT;
	else if (!ft_strncmp(token->value, ">>", len))
		token->type = T_OUT_APPEND;
}

void	ft_set_other(t_all *all)
{
	int		i;
	t_token	*token;

	i = 0;
	while (i < all->token_count)
	{
		token = &all->tokens[i];
		if (i != 0)
			printf("> [%d] - [%d]\n ", token->type, all->tokens[i - 1].type);
		if ((i == 0 && token->type != T_OPERATOR) || (i != 0 && i < all->token_count - 1
				&& all->tokens[i - 1].type == T_OPERATOR))
			token->type = T_COMMAND;
		i++;
	}
	i = 0;
	while (i > all->token_count)
	{
		ft_set_operator(token);
		i++;
	}
}
// echo "$VAR1 $VAR2" | grep -E "hello|world" > output.txt && (cat output.txt | grep "hello" && echo "Found hello" >> output.txt) || echo "Failed to find hello" >> output.txt
