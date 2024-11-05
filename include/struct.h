/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazafin <arazafin@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 11:17:40 by arazafin          #+#    #+#             */
/*   Updated: 2024/11/05 10:33:09 by arazafin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_token
{
	int				type;
	int				second_type;
	char			*value;
}					t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_expand
{
	char	*result;
	int		i;
	int		tok_i;
}	t_expand;

typedef struct s_all
{
	size_t			i;
	int				in_quotes;
	char			current_token[CMD_MAX];
	int				token_index;
	char			quote_char;
	char			*cmd;
	t_token			tokens[TOKENS_MAX];
	int				token_count;
	t_env			*env;
	int				pos;
	int				nb_cmd;
	int				statloc;
	int				exit_status;
	int				child_pid;
	int				fd[2];
	int				tmp;
	int				has_pipe;
	int				has_in;
	int				has_out;
	int				sh;
	char			*infile;
	char			*outfile;
	int				out_type;
	int				x;
	char			*hd_file;
	int				hd_expand;
	int				second;
}					t_all;

typedef struct s_dir
{
	char			*name;
	int				type;
	struct s_dir	*next;
}					t_dir;
#endif
