#include "../../include/minishell.h"

void	ft_expander_exit_status(t_all *all, t_token *token, int i)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	char	*exit_status;

	tmp = ft_substr(token->value, 0, i);
	tmp2 = ft_substr(token->value, i + 2, ft_strlen(token->value) - i - 2);
	exit_status = ft_itoa(all->exit_status);
	tmp3 = ft_strjoin(tmp, exit_status);
	free(token->value);
	token->value = ft_strjoin(tmp3, tmp2);
	free(tmp);
	free(tmp2);
	free(tmp3);
	free(exit_status);
}

void	ft_expander_env(t_token *token, int i)
{
	char	*tmp;
	char	*env;

	env = getenv(token->value + i + 1);
	if (env == NULL)
		env = ft_strdup("");
	tmp = ft_substr(token->value, 0, i);
	free(token->value);
	token->value = ft_strjoin(tmp, env);
	free(tmp);
	free(env);
}

int	ft_expander_word(t_all *all, t_token *token)
{
	int	i;

	i = 0;
	while (token->value[i])
	{
		if (token->value[i] == '$')
		{
			if (token->value[i + 1] == '?')
				ft_expander_exit_status(all, token, i);
			else if (ft_isalpha(token->value[i + 1]))
				ft_expander_env(token, i);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_expander(t_all *all)
{
	int	i;

	i = 0;
	while (all->tokens[i].type != T_END)
	{
		if (all->tokens[i].type == T_WORD || all->tokens[i].type == T_COMMAND)
			ft_expander_word(all, &all->tokens[i]);
		i++;
	}
	return (0);
}
