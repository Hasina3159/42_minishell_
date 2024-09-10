// #include "../../include/minishell.h"

// void	ft_expander_exit_status(t_all *all, t_token *token, int i)
// {
// 	char	*tmp;
// 	char	*tmp2;
// 	char	*tmp3;
// 	char	*exit_status;

// 	tmp = ft_substr(token->value, 0, i);
// 	tmp2 = ft_substr(token->value, i + 2, ft_strlen(token->value) - i - 2);
// 	exit_status = ft_itoa(all->exit_status);
// 	tmp3 = ft_strjoin(tmp, exit_status);
// 	free(token->value);
// 	token->value = ft_strjoin(tmp3, tmp2);
// 	free(tmp);
// 	free(tmp2);
// 	free(tmp3);
// 	free(exit_status);
// }

// static int	get_key_sublen(int i, t_token *token)
// {
// 	int		len;

// 	len = i + 1;
// 	while (ft_isalnum(token->value[len]) || token->value[len] == '_')
// 		len++;
// 	return (len);
// }

// static char	*new_value(char *before, char *env, char *after)
// {
// 	char	*out;
// 	char	*tmp;

// 	if (before[0] == '\0' || before == NULL)
// 	{
// 		if (!env)
// 			tmp = ft_strdup("");
// 		else
// 			tmp = ft_strdup(env);
// 	}
// 	else if (!env)
// 		tmp = ft_strdup(before);
// 	else
// 		tmp = ft_strjoin(before,env);
// 	out = ft_strjoin(tmp, after);
// 	free(tmp);
// 	return (out);
// }

// void	ft_expander_env(t_env *env, t_token *token, int i)
// {
// 	char	*before;
// 	char	*after;
// 	char	*key;
// 	t_env	*tmp_env;

// 	tmp_env = env;
// 	key = ft_substr(token->value, i + 1, get_key_sublen(i, token));
// 		before = ft_substr(token->value, 0, i);
// 	after = ft_substr(token->value, get_key_sublen(i, token), ft_strlen(token->value));
// 	while (tmp_env)
// 	{
// 		if (!ft_strncmp(tmp_env->key, key, ft_strlen(key) - 1))
// 			break ;
// 		tmp_env = tmp_env->next;
// 	}
// 	free(token->value);
// 	if (tmp_env != NULL)
// 		token->value = new_value(before, tmp_env->value, after);
// 	else
// 		token->value = new_value(before, NULL, after);
// 	free(key);
// 	free(before);
// 	free(after);
// }

// int	ft_expander_word(t_all *all, t_token *token)
// {
// 	int	i;

// 	i = 0;
// 	while (token->value[i])
// 	{
// 		if (token->value[i] == '$')
// 		{
// 			if (token->value[i + 1] == '?')
// 				ft_expander_exit_status(all, token, i);
// 			else if (ft_isalpha(token->value[i + 1]) || token->value[i + 1] == '_')
// 				ft_expander_env(all->env, token, i);
// 			i = 0;
// 			continue ;
// 		}
// 		i++;
// 	}
// 	return (0);
// }

// int	ft_expander(t_all *all)
// {
// 	int	i;

// 	i = 0;
// 	while (all->tokens[i].type != T_END)
// 	{
// 		if (all->tokens[i].type == T_WORD || all->tokens[i].type == T_COMMAND)
// 		{
// 			ft_expander_word(all, &all->tokens[i]);
// 		}
// 		i++;
// 	}
// 	return (0);
// }
