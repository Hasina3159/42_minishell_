#include "../../include/minishell.h"

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

void	ft_move_token_0(t_all *all)
{
	t_token	tmp;
	t_token	tmp1;
	int		i;
	int		j;

	i = 0;
	while (i < all->token_count - 1)
	{
		if (all->tokens[i].type == T_FILE_OUT)
		{
			i++;
			tmp.type = all->tokens[i].type;
			tmp.value = all->tokens[i].value;
			all->tokens[i].type = T_PIPE;
			all->tokens[i].value = ft_strdup("|");
			j = i + 1;
			all->token_count = all->token_count + 1;
			while (j < all->token_count)
			{
				tmp1.type = all->tokens[j].type;
				tmp1.value = all->tokens[j].value;
				all->tokens[j].type = tmp.type;
				all->tokens[j].value = tmp.value;
				tmp.type = tmp1.type;
				tmp.value = tmp1.value;
				j++;
			}
		}
		i++;
	}
}

void	ft_move_token(t_all *all)
{
	t_token	tmp;
	t_token	tmp1;
	int		i;
	int		j;

	i = 0;
	while (i < all->token_count - 1)
	{
		if (all->tokens[i].type == T_FILE_OUT)
		{
			all->tokens[i].type = T_WORD;
			tmp.type = all->tokens[i].type;
			tmp.value = all->tokens[i].value;
			all->tokens[i].type = T_COMMAND;
			all->tokens[i].value = ft_strdup("/usr/bin/tee");
			j = i + 1;
			all->token_count = all->token_count + 1;
			while (j < all->token_count)
			{
				tmp1.type = all->tokens[j].type;
				tmp1.value = all->tokens[j].value;
				all->tokens[j].type = tmp.type;
				all->tokens[j].value = tmp.value;
				tmp.type = tmp1.type;
				tmp.value = tmp1.value;
				j++;
			}
		}
		i++;
	}
}

void	ft_move_token_2(t_all *all)
{
	t_token	tmp;
	t_token	tmp1;
	int		i;
	int		j;

	i = 0;
	while (i < all->token_count - 1)
	{
		if (i > 0 && !ft_strncmp(all->tokens[i].value, "/usr/bin/tee", 13) && !ft_strncmp(all->tokens[i - 1].value, ">>", 2))
		{
			i++;
			all->tokens[i].type = T_WORD;
			tmp.type = all->tokens[i].type;
			tmp.value = all->tokens[i].value;
			all->tokens[i].type = T_WORD;
			all->tokens[i].value = ft_strdup("-a");
			j = i + 1;
			all->token_count = all->token_count + 1;
			while (j < all->token_count)
			{
				tmp1.type = all->tokens[j].type;
				tmp1.value = all->tokens[j].value;
				all->tokens[j].type = tmp.type;
				all->tokens[j].value = tmp.value;
				tmp.type = tmp1.type;
				tmp.value = tmp1.value;
				j++;
			}
		}
		i++;
	}
}

void	ft_redir_to_pipe(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->token_count)
	{
		if (all->tokens[i].type == T_OUT || (all->tokens[i].type == T_OUT_APPEND))
		{
			free(all->tokens[i].value);
			all->tokens[i].value = ft_strdup("|");
			all->tokens[i].type = T_PIPE;
		}
		i++;
	}
}

int	ft_tokenize(t_all *all)
{

	ft_init_t_all(all);
	ft_create_token(all);
	ft_replace_all_vars(all);
	//ft_replace_all_wildcards(all);
	ft_set_command(all);
	ft_set_other(all);
	ft_set_other_1(all);
	ft_finalize_token(all);
	// if (input_error(all))
	// 	return (1);
	ft_move_token_0(all);
	ft_move_token(all);
	ft_move_token_2(all);
	ft_redir_to_pipe(all);
	ft_print_tokens(all);
	return (0);
}

// int	main(void)
// {
// 	char	*cmd;
// 	t_all	all;
// 	//t_dir	**dirs;
// 	//char	*wildcard;
// 	int		i;

// 	signal(SIGINT, ft_ctrl_c);
// 	all.tmp = -1;
// 	while (1)
// 	{
// 		cmd = readline("Entrez une commande : ");
// 		if (cmd == NULL)
// 		{
// 			//perror("Erreur de lecture!");
// 			printf("exit !\n");
// 			return (1);
// 		}
// 		if (strlen(cmd) > CMD_MAX)
// 		{
// 			perror("Too long!");
// 			free(cmd);
// 			return (1);
// 		}
// 		if (ft_strlen(cmd))
// 			add_history(cmd);

// 		printf("VALUE : %s\n", ft_getvarvalue(&all, cmd));
// 		ft_tokenize(&all, cmd);
// 		printf("\n");
// 		//printf("match : %d", ft_match(all.tokens[1].value,
// 		//		all.tokens[0].value));
// 		printf("\n");
// 		//dirs = ft_init_dirs();
// 		//ft_copy_dir(dirs, ft_strlen(getcwd(NULL, 0)) + 1);
// 		//ft_print_tokens(&all);
// 		//ft_show_sanitized_command(&all);
// 		//wildcard = ft_get_wildcard(dirs, "test");
// 		//printf("\n>>>>>>>>>>>>> FINAL : %s\n\n", all.tokens[0].value);
// 		//printf("\n>>>>>>>>>>>>> WILDCARD : [%s]\n\n", wildcard);
// 		//ft_show_match(dirs);
// 		//ft_print_tokens(&all);
// 		i = 0;
// 		ft_execute_all(&all, &i);
// 		free(cmd);
// 	}
// 	return (0);
// }
