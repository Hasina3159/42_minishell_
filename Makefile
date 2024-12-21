NAME		= minishell
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -rf
MKDIR_P		= mkdir -p

SRCS_PATH	= ./srcs
OBJS_PATH	= ./objs
LIBFT_PATH	= ./libft

SRCS		= ./libft/ft_atoi.c ./libft/ft_bzero.c ./libft/ft_calloc.c ./libft/ft_isalnum.c ./libft/ft_isalpha.c ./libft/ft_isascii.c ./libft/ft_isdigit.c ./libft/ft_isprint.c ./libft/ft_itoa.c ./libft/ft_lstadd_back.c ./libft/ft_lstadd_front.c ./libft/ft_lstclear.c ./libft/ft_lstdelone.c ./libft/ft_lstiter.c ./libft/ft_lstlast.c ./libft/ft_lstmap.c ./libft/ft_lstnew.c ./libft/ft_lstsize.c ./libft/ft_memchr.c ./libft/ft_memcmp.c ./libft/ft_memcpy.c ./libft/ft_memmove.c ./libft/ft_memset.c ./libft/ft_putchar_fd.c ./libft/ft_putendl_fd.c ./libft/ft_putnbr_fd.c ./libft/ft_putstr_fd.c ./libft/ft_split.c ./libft/ft_strchr.c ./libft/ft_strdup.c ./libft/ft_striteri.c ./libft/ft_strjoin.c ./libft/ft_strlcat.c ./libft/ft_strlcpy.c ./libft/ft_strlen.c ./libft/ft_strmapi.c ./libft/ft_strncmp.c ./libft/ft_strnstr.c ./libft/ft_strrchr.c ./libft/ft_strtrim.c ./libft/ft_substr.c ./libft/ft_tolower.c ./libft/ft_toupper.c ./srcs/tokenizer/tokenizer_beta.c ./srcs/tokenizer/tokenizer_beta_0.c ./srcs/tokenizer/lex.c ./srcs/tokenizer/tokenizer.c ./srcs/tokenizer/tokenizer_0.c ./srcs/tokenizer/tokenizer_1.c ./srcs/tokenizer/tokenizer_2.c ./srcs/tokenizer/tokenizer_3.c ./srcs/tokenizer/tokenizer_alpha.c ./srcs/utils/std.c ./srcs/utils/tok_utils.c ./srcs/utils/clean.c ./srcs/utils/env_utils.c ./srcs/utils/ft_count_splitted.c ./srcs/utils/ft_getvalue.c ./srcs/utils/ft_str_repl_copy.c ./srcs/utils/remove_quotes.c ./srcs/utils/print_error.c ./srcs/utils/get_next_line.c ./srcs/utils/get_next_line_utils.c ./srcs/utils/another_utils.c ./srcs/utils/utils_1.c ./srcs/utils/better_strjoin.c ./srcs/utils/ft_count_char.c ./srcs/utils/ft_count_wildcards.c ./srcs/utils/ft_is_operator.c ./srcs/utils/ft_is_sep.c ./srcs/utils/ft_is_varchar.c ./srcs/utils/ft_isspace.c ./srcs/utils/ft_replace_str.c ./srcs/utils/ft_show_sanitized_command.c ./srcs/utils/ft_str_repl.c ./srcs/utils/ft_strndup.c ./srcs/utils/utils_0.c ./srcs/builtins/cd.c ./srcs/builtins/echo.c ./srcs/builtins/env.c ./srcs/builtins/exit.c ./srcs/builtins/export.c ./srcs/builtins/pwd.c ./srcs/builtins/unset.c ./srcs/builtins/ft_echo.c ./srcs/executor/ht_utils_0.c ./srcs/executor/exec.c ./srcs/executor/exec_utils.c ./srcs/executor/exec_utils1.c ./srcs/executor/exec_utils2.c ./srcs/executor/exec_utils3.c ./srcs/executor/exit_status.c ./srcs/executor/ft_pipe.c ./srcs/executor/get_hd_str.c ./srcs/executor/get_predecence.c ./srcs/executor/handle_redin.c ./srcs/executor/handle_redout.c ./srcs/executor/hd_utils.c ./srcs/executor/heredoc.c ./srcs/executor/history.c ./srcs/executor/signal.c ./srcs/executor/signal2.c ./srcs/expander/expand_u.c ./srcs/expander/expander.c ./srcs/expander/expander_test.c ./srcs/minishell/init.c ./srcs/minishell/minishell.c ./srcs/minishell/input_error/renorm.c ./srcs/minishell/input_error/test_hd_in.c ./srcs/minishell/input_error/test_out_append.c ./srcs/minishell/input_error/user_input_error.c
OBJS		= $(patsubst $(SRCS_PATH)/%.c,$(OBJS_PATH)/%.o,$(SRCS))


all: $(NAME)

$(OBJS_PATH)/%.o: $(SRCS_PATH)/%.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	make -C $(LIBFT_PATH)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L$(LIBFT_PATH) -lft -lreadline

clean:
	$(RM) $(OBJS_PATH)
	make -C $(LIBFT_PATH) clean

fclean: clean
	$(RM) $(NAME) .history
	make -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re
