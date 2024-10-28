/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazafin <arazafin@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 08:59:34 by arazafin          #+#    #+#             */
/*   Updated: 2024/10/11 22:28:47 by arazafin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

int		ft_count_args(char **args);
int		ft_count_words(char const *s);
int		ft_isspace(char c);
int		ft_is_sep(char c);
int		ft_is_operator(char c);
int		ft_count_occurences(char *text, char *sub);
int		ft_str_repl(char *text, char *from, char *to);
char	*ft_getvarvalue(t_all *all, char *var);
int		ft_is_varchar(char c);
char	*ft_strndup(const char *s, int len);
void	ft_show_sanitized_command(t_all *all);
char	*better_strjoin(char *s1, char const *s2);
int		ft_count_char(char *s, char c);
void	ft_opendir(char *path, DIR **dir);
void	ft_closedir(DIR **dir);
int		ft_isdir(char *path);
t_dir	*ft_create_dir(char *name, int type);
void	ft_add_dir(t_dir **lst, t_dir *elem);
void	ft_show_all_dirs(t_dir **dirs);
t_dir	**ft_init_dirs(void);
void	ft_replace_str(char **src, char *to);
void	ft_show_match(t_dir **dirs);
int		ft_count_wildcards(char *w);
char	*ft_get_wildcard(t_dir **dirs, char *w);
char	*ft_str_repl_copy(char *text, char *from, char *to);
int		ft_count_splitted(char **splitted);
char	*ft_is_in_env(t_all *all, char *var);
void	print_error(char *name, char *arg, char *error);
// * env_utils.c
int		ft_search_key(char *key, t_all *all);
char	*ft_get_env(char *key, t_all *all);
int		ft_setvarvalue(t_all *all, char *key, char *value);

#endif
