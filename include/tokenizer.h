#ifndef TOKENIZER_H
# define TOKENIZER_H

void				ft_init_t_all(t_all *all);
void				ft_add_token(t_all *all, int type, char *value);
int					ft_start_quotes(t_all *all);
int					ft_in_quotes_operation(t_all *all);
void				ft_sep_operation(t_all *all);
void				ft_set_operator(t_token *token);
void				ft_set_other(t_all *all);
int					ft_is_sep(char c);
void				ft_create_token(t_all *all);
void				ft_print_tokens(t_all *all);
char				*ft_show_token(t_token *token);
void				ft_set_command(t_all *all);
char				**ft_get_all_var(char *s);
void				ft_show_all_var(char **var);
int					ft_replace_all_vars(t_all *all);
int					ft_replace_var(t_all *all, t_token *token);
void				ft_finalize_token(t_all *all);
void				ft_tokenize(t_all *all);
int					ft_match_one(char *s, char next);
int					ft_match(char *s, char *w);
void				ft_dirmatch(char *path, char *w, int n);
int					ft_count_dir(char *path);
t_dir				**ft_copy_dir(t_dir **dirs, int len_cwd);
t_dir				**ft_aaa(t_dir **dirs);
t_dir				**ft_get_all_dirs(t_dir **dirs, int i, t_dir *tmp);
int					ft_is_t_op(int type);
void				ft_set_other_1(t_all *all);

#endif
