#ifndef BUILTINS_H
# define BUILTINS_H

int					ft_echo(int argc, char **argv);
// int					ft_cd(char **av, t_env **env);
int	ft_cd(char **av, t_all *all);
int					ft_pwd(t_all *all);
int					ft_export(t_all *all, char **av);
int					ft_env(t_all *all);
int					ft_unset(t_all *all, char **av);
int					ft_exit(t_all *all, char **argv);

#endif
