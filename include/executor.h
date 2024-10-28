/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazafin <arazafin@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 11:17:25 by arazafin          #+#    #+#             */
/*   Updated: 2024/10/11 22:24:37 by arazafin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

// int		ft_execute(t_all *all, int *i);
int		ft_execute_all(t_all *all, int *i);
// int		get_token_precedence(t_token *token);
void	ft_ctrl_c(int sig);
void	execve_cmd(char **cmd, char **envp);
// * handle_redin.c
char	*get_infile(t_all *all, int i);
int		check_file(char *file, t_all *all, int f);
int		handle_redin(t_all *all);
// * heredoc
void	heredoc(t_all *all, t_token lim);
void	hd_expand(t_all *all, char *line);
// * handle_redout.c
// int		open_outfile(t_all *all, int type);
int		f_op(int type);
char	*get_outfile(t_all *all, int i);
int		handle_redout(t_all *all);
// * ft_pipe
int		ft_pipe(t_all *all);
// * exit_status.c
void	get_exit_status(t_all *all);
// * exec_utils
char	**create_envp(t_all *all);
// * exec_utils1
int		is_n_op(int type);
void	is_need_pipe(t_all *all, int *i);
int		ft_has_op_before(t_all *all, int *i, int type);
void	reset_redirection(t_all *all, int *x);
// *exec_utils2
char	**ft_tokens_to_char(t_all *all, int *i);
int		is_built(char **av);
int		use_built(t_all *all, int ch, char **cmd);;
void	parent_process(t_all *all);

#endif
