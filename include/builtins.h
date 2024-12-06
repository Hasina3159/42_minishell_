/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:20:55 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/12/06 10:20:58 by ntodisoa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

// int	ft_echo(int argc, char **argv);
int	ft_echo(int argc, char **argv, t_all *all);
int	ft_cd(char **av, t_all *all);
int	ft_pwd(t_all *all);
int	ft_export(t_all *all, char **av);
int	is_valid_arg(char *arg);
int	ft_env(t_all *all);
int	ft_unset(t_all *all, char **av);
int	ft_exit(t_all *all, char **argv);

#endif
