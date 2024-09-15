#ifndef EXECUTOR_H
# define EXECUTOR_H

char				**ft_tokens_to_char(t_all *all, int *i);
int					ft_execute(t_all *all, int *i, const char *in);
int					ft_execute_all(t_all *all, int *i);
int					get_token_precedence(t_token *token);
int					ft_has_pipe_after(t_all *all, int *i);
void				ft_ctrl_c(int sig);
void	execve_cmd(char **cmd, char **envp);
void	heredoc(t_all *all, char *limiter);
char	*get_infile(t_all *all, int i);

#endif
