/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazafin <arazafin@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 11:17:25 by arazafin          #+#    #+#             */
/*   Updated: 2024/10/30 21:11:19 by arazafin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

int		ft_execute(t_all *all, int *i);
int		ft_execute_all(t_all *all, int *i);
int		get_token_precedence(t_token *token);
void	execve_cmd(char **cmd, char **envp);
// * handle_redin.c
char	*get_infile(t_all *all, int i, int *stat);
int		check_file(char *file, t_all *all, int f);
int		handle_redin(t_all *all);
// * heredoc
char	*get_heredoc(char *doc, char *line);
int		hd_signal(char *line, char *limiter);
int		is_limiter(char *limiter, char *line);
int		here_doc(t_token lim, int fd_out, t_all *all);
void	hd_expand(t_all *all, char *line);
int		heredoc(t_all *all, t_token lim);
// * handle_redout.c
int		open_outfile(t_all *all, int type);
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
void	is_need_pipe(t_all *all, int *i);
int		ft_has_op_before(t_all *all, int *i, int type);
int		ft_has_op_after(t_all *all, int *i);
void	reset_redirection(t_all *all, int *x);
// *exec_utils2
char	**ft_tokens_to_char(t_all *all, int *i);
int		is_built(char **av);
int		use_built(t_all *all, int ch, char **cmd);;
void	parent_process(t_all *all);
// *exec_utils3
int		check_redin(t_all *all);
int		check_redir(t_all *all, int *i, int *x, int *ret);
// *signal test
void	setup_signal(int sig, t_state state);
void	ft_sigint(int sig, siginfo_t *info, void *ucontext);
void	reset_parent_sig(void);
void	setup_parent_signals(void);
void	setup_child_signals(void);
// *utils/std.c
void	new_std(char *nstd);

#endif
