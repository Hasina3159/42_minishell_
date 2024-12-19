NAME		= minishell
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -rf
MKDIR_P		= mkdir -p

SRCS_PATH	= ./srcs
OBJS_PATH	= ./objs
LIBFT_PATH	= ./libft

SRCS		= $(shell find $(SRCS_PATH) -name "*.c")
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
	$(RM) $(NAME) .fake_clone
	make -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re
