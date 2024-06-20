NAME			=	minishell

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
RM				=	rm -rf

SRCS_PATH		=	./philo
SRCS 			=	$(shell find . -name "*.c" | grep ./srcs/ | tr '\n' ' ')
OBJS			=	$(SRCS:.c=.o)


$(SRCS_PATH)/%.o:		%.c
					$(CC) $(CFLAGS) -c $< -o $@

$(NAME):			$(OBJS)
					make -C libft
					$(CC) $(CFLAGS) $(SRCS) -o $(NAME) -g

all:				$(NAME)

$(BONUS):
	$(CC) $(CFLAGS) $(SRCS_BONUS) -o $(NAME) -g

bonus:				$(BONUS)

clean:
					$(RM) $(OBJS) $(OBJS_BONUS)
					make -C libft clean

fclean:				clean
					$(RM) $(NAME) $(BONUS)

re:					fclean all

.PHONY:				all clean fclean re