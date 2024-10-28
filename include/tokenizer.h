/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arazafin <arazafin@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 08:59:29 by arazafin          #+#    #+#             */
/*   Updated: 2024/10/11 22:22:44 by arazafin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

void	ft_init_t_all(t_all *all);
void	ft_add_token(t_all *all, int type, char *value);
int		ft_start_quotes(t_all *all);
int		ft_in_quotes_operation(t_all *all);
void	ft_sep_operation(t_all *all);
void	ft_set_operator(t_token *token);
void	ft_set_other(t_all *all);
int		ft_is_sep(char c);
void	ft_set_command(t_all *all);
char	**ft_get_all_var(char *s);
int		ft_replace_all_vars(t_all *all);
void	ft_finalize_token(t_all *all);
int		ft_tokenize(t_all *all);
int		ft_match(char *s, char *w);
t_dir	**ft_copy_dir(t_dir **dirs, int len_cwd);
void	ft_set_other_1(t_all *all);
int		op_last_pos(char *input);
void	append_to_prompt(char **input);
void	ft_set_other_2(t_all *all);
void    ft_copy_token(t_token *src, t_token *dst);
t_token *ft_create_copy_token(t_all *all);
void    ft_restore_token(t_all *all, t_token *tokens);

#endif
