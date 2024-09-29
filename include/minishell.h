/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazafin <arazafin@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 18:05:25 by arazafin          #+#    #+#             */
/*   Updated: 2024/09/29 14:44:21 by arazafin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <dirent.h>
# include <sys/syscall.h>
# include <string.h>
# include <errno.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include "../libft/libft.h"
# include "define.h"
# include "struct.h"
# include "builtins.h"
# include "executor.h"
# include "utils.h"
# include "tokenizer.h"

int	ft_expander(t_all *all);
// ? init
void	init_shell(t_all *all);
// ? exit
void	del_token(t_all *all);
int		free_all(t_all *all);
// ? utils/clean.c
void	free_split(char **cmd);
int	clean_child(t_all *all);
int	clean_child_b(t_all *all, char **token_str);
void	del_env(t_env **env);
// ? imput_error
int	test_hd_in(t_token *tokens, int i);
int	test_out_n_append(t_token *tokens, int i);
int	input_error(t_all *all);


#endif
