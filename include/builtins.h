#ifndef BUILTINS_H
# define BUILTINS_H

int					ft_echo(int argc, char **argv);
int					ft_cd(char **argv);
int					ft_pwd(int argc, char **argv);
int					ft_export(t_all *all, char **av);
int					ft_env(t_all *all);
int					ft_unset(t_all *all, char **av);
void				ft_exit(t_all *all, char **argv);

#endif
