/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntodisoa <ntodisoa@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:21:49 by ntodisoa          #+#    #+#             */
/*   Updated: 2024/12/20 12:26:35 by ntodisoa         ###   ########.fr       */
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
void	ft_replace_str(char **src, char *to);
int		ft_count_wildcards(char *w);
char	*ft_str_repl_copy(char *text, char *from, char *to);
int		ft_count_splitted(char **splitted);
char	*ft_is_in_env(t_all *all, char *var);
void	print_error(char *name, char *arg, char *error);
// * env_utils.c
int		ft_search_key(char *key, t_all *all);
char	*ft_get_env(char *key, t_all *all);
int		ft_setvarvalue(t_all *all, char *key, char *value);
void	update_underscore(t_all *all);
char	*ft_remove_quotes(char *s);
// * tok_utils.c
int		i_n_op(int type);
int		is_n_op(int type);
int		count_cmd(t_all *all);
// * expand_u.c
char	*get_env_value(t_env *env, char *key);
char	*ft_strjoin_free(char *s1, char *s2);
int		env_size(t_env *env);
int		ft_is_separator(char c);
int		ft_is_quotes(char c);
void	ft_pass_separator(char const *s, int *i, int *count, int *is_in_a_str);
char	*get_next_line(int fd);
int		another_condition(char *value, char **key, t_env **tmp);

#endif
