#include "../../include/minishell.h"

void	ft_set_operator(t_token *token)
{
	int	len;

	len = ft_strlen(token->value);
	if (len == 0)
	{
		token->type = T_END;
		return ;
	}
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
	else if (!ft_strncmp(token->value, "<<", len))
		token->type = T_HD;
}

char	*ft_show_token(t_token *token)
{
	int	len;

	len = ft_strlen(token->value);
	if (len == 0)
		return "END";
	if (!ft_strncmp(token->value, "|", len))
		return "PIPE";
	else if (!ft_strncmp(token->value, "||", len))
		return "OR";
	else if (!ft_strncmp(token->value, "&&", len))
		return "AND";
	else if (!ft_strncmp(token->value, "(", len))
		return "P_OPEN";
	else if (!ft_strncmp(token->value, ")", len))
		return "P_CLOSE";
	else if (!ft_strncmp(token->value, "<", len))
		return "RED_IN";
	else if (!ft_strncmp(token->value, ">", len))
		return "RED_OUT";
	else if (!ft_strncmp(token->value, ">>", len))
		return "RED_APPEND";
	else if (!ft_strncmp(token->value, "<<", len))
		return "HERE_DOC";
	else if (token->type == T_COMMAND)
		return "COMMAND";
	else if (token->type == T_WORD)
		return "ARG";
	else if (token->type == T_STRING_S)
		return "STRING_S";
	else if (token->type == T_STRING_D)
		return "STRING_D";
	else if (token->type == T_FILE_OUT)
		return "FILE_OUT";
	else if (token->type == T_FILE_IN)
		return "FILE_IN";
	else if (token->type == T_HD_ENDER)
		return "T_HD_ENDER";
	else
		return "END";
}

int	ft_is_t_op(int type)
{
	if (type != T_WORD && type != T_COMMAND && type != T_STRING_S && type != T_STRING_D)
		return (1);
	return (0);
}

void	ft_set_command(t_all *all)
{
	int		i;
	t_token	*token;

	i = 0;
	while (i < all->token_count)
	{
		token = &all->tokens[i];
		if ((i == 0 && !ft_is_t_op(token->type)) || (i != 0 && i < all->token_count - 1
				&& ft_is_t_op(all->tokens[i - 1].type)  && !ft_is_t_op(token->type)))
			token->type = T_COMMAND;
		i++;
	}
}

void	ft_set_other(t_all *all)
{
	int		i;
	t_token	*token;
	t_token	*prec;
	int		len;

	i = 0;
	while (i < all->token_count)
	{
		token = &all->tokens[i];
		len = ft_strlen(token->value);
		if (len == 0)
			break ;
		prec = NULL;
		if (i != 0)
			prec = &all->tokens[i - 1];
		if (prec && !ft_is_t_op(token->type))
		{
			if (!ft_strncmp(prec->value, ">", ft_strlen(prec->value)) || !ft_strncmp(prec->value, ">>", ft_strlen(prec->value)))
			{
				token->type = T_FILE_OUT;
				i++;
				continue ;
			}
			else if (!ft_strncmp(prec->value, "<", ft_strlen(prec->value)))
			{
				token->type = T_FILE_IN;
				i++;
				continue ;
			}
			else if (!ft_strncmp(prec->value, "<<", ft_strlen(prec->value)))
			{
				token->type = T_HD_ENDER;
				i++;
				continue ;
			}
		}
		i++;
	}
	i = 0;
	while (i < all->token_count)
	{
		token = &all->tokens[i];
		ft_set_operator(token);
		i++;
	}
}

void	ft_set_other_1(t_all *all)
{
	int		i;
	t_token	*token;

	i = 0;
	while (i < all->token_count)
	{
		token = &all->tokens[i];
		if (token->type == T_STRING_D || token->type == T_STRING_S)
			token->type = T_WORD;
		i++;
	}
}


// echo"$VAR1 $VAR2"|grep -E"hello|world">output.txt&&(cat output.txt|grep"hello"&&echo"Found hello">>output.txt)||echo "Failed to find hello">>output.txt
