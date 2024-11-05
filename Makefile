NAME		= minishell
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -rf
MKDIR_P		= mkdir -p

RED			= \e[31m
GREEN		= \e[32m
YELLOW		= \e[33m
BLUE		= \e[34m
RESET		= \e[0m

SRCS_PATH	= ./srcs
OBJS_PATH	= ./objs
LIBFT_PATH	= ./libft

SRCS		= $(shell find $(SRCS_PATH) -name "*.c")
OBJS		= $(patsubst $(SRCS_PATH)/%.c,$(OBJS_PATH)/%.o,$(SRCS))

TOTAL_FILES	= $(words $(SRCS))
CURRENT_FILE	= 1

all: $(NAME)

$(OBJS_PATH)/%.o: $(SRCS_PATH)/%.c
	@$(MKDIR_P) $(dir $@)
	@printf "\r$(YELLOW)Compiling [%3d%%] [%-50s] %d/%d$(RESET)" \
		$(shell echo $$(($(CURRENT_FILE)*100/$(TOTAL_FILES)))) \
		`printf '%*s' $$(($(CURRENT_FILE)*50/$(TOTAL_FILES))) | tr ' ' '#'` \
		$(CURRENT_FILE) $(TOTAL_FILES)
	@$(CC) $(CFLAGS) -c $< -o $@
	@$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE)+1))))

$(NAME): .fake_clone $(OBJS)
	@echo  "\n$(GREEN)Compilation completed!$(RESET)"
	@echo  "$(BLUE)Building $(NAME)...$(RESET)"
	@make -C $(LIBFT_PATH) > /dev/null 2>&1
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L$(LIBFT_PATH) -lft -lreadline
	@echo  "$(GREEN)$(NAME) successfully created!$(RESET)"

.fake_clone:
	@if [ ! -f $(NAME) ]; then \
		echo  "$(BLUE)git clone git@github.com:RandomBash/42_minishell_.git $(NAME)$(RESET)"; \
		echo  "$(GREEN)Cloning into '$(NAME)'...$(RESET)"; \
		sleep 1; \
		printf "$(YELLOW)remote: Enumerating objects: 0, counting...$(RESET)"; \
		for i in $$(seq 0 90 893); do \
			printf "\r$(YELLOW)remote: Enumerating objects: %-3d, counting...$(RESET)" $$i; \
			sleep 0.1; \
		done; \
		printf "\r$(YELLOW)remote: Enumerating objects: 893, done.        $(RESET)\n"; \
		sleep 0.5; \
		printf "$(YELLOW)remote: Counting objects: 0%% (0/893)...$(RESET)"; \
		for i in $$(seq 0 90 893); do \
			printf "\r$(YELLOW)remote: Counting objects: %3d%% (%d/893)...$(RESET)" $$((i * 100 / 893)) $$i; \
			sleep 0.1; \
		done; \
		printf "\r$(YELLOW)remote: Counting objects: 100%% (893/893), done.        $(RESET)\n"; \
		sleep 0.5; \
		printf "$(YELLOW)remote: Compressing objects: 0%% (0/451)...$(RESET)"; \
		for i in $$(seq 0 45 451); do \
			printf "\r$(YELLOW)remote: Compressing objects: %3d%% (%d/451)...$(RESET)" $$((i * 100 / 451)) $$i; \
			sleep 0.1; \
		done; \
		printf "\r$(YELLOW)remote: Compressing objects: 100%% (451/451), done.        $(RESET)\n"; \
		sleep 0.5; \
		echo  "$(YELLOW)remote: Total 893 (delta 553), reused 744 (delta 408), pack-reused 0 (from 0)$(RESET)"; \
		sleep 0.5; \
		printf "$(BLUE)Receiving objects: 0%% (0/893)$(RESET)"; \
		for i in $$(seq 0 89 893); do \
			printf "\r$(BLUE)Receiving objects: %3d%% (%d/893)$(RESET)" $$((i * 100 / 893)) $$i; \
			sleep 0.1; \
		done; \
		printf "\r$(BLUE)Receiving objects: 100%% (893/893)$(RESET)\n"; \
		printf "$(BLUE)Resolving deltas: 0%% (0/553)$(RESET)"; \
		for i in $$(seq 0 55 553); do \
			printf "\r$(BLUE)Resolving deltas: %3d%% (%d/553)$(RESET)" $$((i * 100 / 553)) $$i; \
			sleep 0.1; \
		done; \
		printf "\r$(BLUE)Resolving deltas: 100%% (553/553)$(RESET)\n"; \
	fi
	@touch .fake_clone

clean:
	@echo  "$(RED)Cleaning object files...$(RESET)"
	@$(RM) $(OBJS_PATH)
	@make -C $(LIBFT_PATH) clean > /dev/null 2>&1
	@echo  "$(GREEN)Clean completed!$(RESET)"

fclean: clean
	@echo  "$(RED)Removing $(NAME)...$(RESET)"
	@$(RM) $(NAME) .fake_clone
	@make -C $(LIBFT_PATH) fclean > /dev/null 2>&1
	@echo  "$(GREEN)Full clean completed!$(RESET)"

re: fclean all

.PHONY: all clean fclean re
