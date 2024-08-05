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

void	ft_create_token(t_all *all)
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
		printf("t_token %d: Value: %s, Type: '%s', ind : %d\n", i,
			all->tokens[i].value, ft_show_token(&all->tokens[i]),
			all->tokens[i].type);
		i++;
	}
}

void	ft_replace_all_wildcards(t_all *all)
{
	char	*wildcard;
	t_dir	**dirs;
	int	i;

	i = 0;
	dirs = ft_init_dirs();
	while (i < all->token_count)
	{
		if (ft_count_char(all->tokens[i].value, '*') && all->tokens[i].type != T_STRING_S)
		{
			ft_copy_dir(dirs, ft_strlen(getcwd(NULL, 0)) + 1);
			wildcard = ft_get_wildcard(dirs, all->tokens[i].value);
			free(all->tokens[i].value);
			all->tokens[i].value = wildcard;
		}
		i++;
	}
	free(dirs);
}

void	ft_tokenize(t_all *all, char *cmd)
{

	ft_init_t_all(all, cmd);
	ft_create_token(all);
	ft_replace_all_vars(all);
	ft_replace_all_wildcards(all);
	ft_set_command(all);
	ft_set_other(all);
	ft_finalize_token(all);
}

int	main(void)
{
	char	*cmd;
	t_all	all;
	t_dir	**dirs;
	char	*wildcard;
	int		i;

	while (1)
	{
		cmd = readline("Entrez une commande : ");
		if (cmd == NULL)
		{
			perror("Erreur de lecture!");
			return (1);
		}
		if (strlen(cmd) > CMD_MAX)
		{
			perror("Too long!");
			free(cmd);
			return (1);
		}
		ft_tokenize(&all, cmd);
		printf("\n");
		//printf("match : %d", ft_match(all.tokens[1].value,
		//		all.tokens[0].value));
		printf("\n");
		dirs = ft_init_dirs();
		ft_copy_dir(dirs, ft_strlen(getcwd(NULL, 0)) + 1);
		ft_print_tokens(&all);
		ft_show_sanitized_command(&all);
		wildcard = ft_get_wildcard(dirs, "test");
		printf("\n>>>>>>>>>>>>> FINAL : %s\n\n", all.tokens[0].value);
		printf("\n>>>>>>>>>>>>> WILDCARD : [%s]\n\n", wildcard);
		//ft_show_match(dirs);
		ft_print_tokens(&all);
		i = 0;
	printf("----------------000 \n");
		ft_execute_all(&all, &i);
	printf("----------------111 \n");

		free(cmd);
	}
	return (0);
}
