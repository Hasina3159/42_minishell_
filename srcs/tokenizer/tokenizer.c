#include "../minishell.h"

void	ft_end_token(t_all *all)
{
	if (all->token_index > 0)
	{
		all->current_token[all->token_index] = 0;
		ft_add_token(all, T_WORD, all->current_token);
	}
	ft_add_token(all, T_END, "");
}

void	ft_tokenize(t_all *all)
{
	while (all->i < ft_strlen(all->cmd))
	{
		if (!ft_in_quotes_operation(all))
		{
			if (ft_isspace(all->cmd[all->i]))
			{
				if (all->token_index > 0)
				{
					all->current_token[all->token_index] = 0;
					ft_add_token(all, T_WORD, all->current_token);
					all->token_index = 0;
				}
			}
			else if (!ft_start_quotes(all) && ft_is_operator(all->cmd[all->i]))
				ft_sep_operation(all);
			else
				all->current_token[all->token_index++] = all->cmd[all->i];
		}
		all->i = all->i + 1;
	}
	ft_end_token(all);
}

void	ft_print_tokens(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->token_count)
	{
		printf("t_token %d: Type: %d, Value: '%s'\n", i, all->tokens[i].type,
			all->tokens[i].value);
		i++;
	}
}

int	main(void)
{
	char	*cmd;
	t_all	all;

	while (1)
	{
		printf("Entrez une commande: ");
		cmd = readline("Entrez une commande : ");
		if (ft_strlen(cmd) > CMD_MAX)
		{
			perror("Too long!");
			return (1);
		}
		if (cmd == NULL)
		{
			perror("Erreur de lecture!");
			return (1);
		}
		ft_init_t_all(&all, cmd);
		ft_tokenize(&all);
		ft_set_other(&all);
		ft_print_tokens(&all);
	}
	return (0);
}
