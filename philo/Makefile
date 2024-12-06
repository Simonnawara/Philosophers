# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sinawara <sinawara@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/29 16:23:18 by sinawara          #+#    #+#              #
#    Updated: 2024/12/06 10:31:13 by sinawara         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
BONUS = philo_bonus
SRCS = main.c
BONUS_SRCS =

CC = gcc
CCFLAG = -Wall -Werror -Wextra

SUCCESS_COLOR = \033[38;2;220;220;200m

OBJ_DIR = obj
BONUS_OBJ_DIR = obj_bonus

OBJECT = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
BONUS_OBJECT = $(addprefix $(BONUS_OBJ_DIR)/, $(BONUS_SRCS:.c=.o))

D_SRCS = ./src/
D_BONUS_SRCS = ./src/src_bonus/

# ASCII logo defined as a shell command
WHITE   = \033[37m
PHILO_WHITE  = \033[38;2;220;220;200m
RED     = \033[31m
BURGUNDY = \033[38;5;88m
BLUE    = \033[34m
GREEN   = \033[32m
MINECRAFT_GREEN = \033[38;5;70m
YELLOW  = \033[33m
PINK    = \033[35m
CYAN    = \033[36m
ORANGE  = \033[38;5;214m
PURPLE	= \033[38;5;93m

LOGO = printf "\n\
$(PHILO_WHITE)░▒▓███████▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░      ░▒▓██████▓▒░  $(PHILO_white)\n\
$(PHILO_WHITE)░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░     ░▒▓█▓▒░░▒▓█▓▒░ $(PHILO_white)\n\
$(PHILO_WHITE)░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░     ░▒▓█▓▒░░▒▓█▓▒░ $(PHILO_white)\n\
$(PHILO_WHITE)░▒▓███████▓▒░░▒▓████████▓▒░▒▓█▓▒░▒▓█▓▒░     ░▒▓█▓▒░░▒▓█▓▒░ $(PHILO_white)\n\
$(PHILO_WHITE)░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░     ░▒▓█▓▒░░▒▓█▓▒░ $(PHILO_white)\n\
$(PHILO_WHITE)░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░     ░▒▓█▓▒░░▒▓█▓▒░ $(PHILO_white)\n\
$(PHILO_WHITE)░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓████████▓▒░▒▓██████▓▒░  $(PHILO_white)\n"



TOTAL_FILES := $(words $(SRCS) $(BONUS_SRCS))
COMPILED_FILES = 0

define progress_bar
    @$(eval COMPILED_FILES=$(shell echo $$(($(COMPILED_FILES) + 1))))
    @if [ $(TOTAL_FILES) -gt 0 ]; then \
        PROGRESS=$$(($(COMPILED_FILES) * 100 / $(TOTAL_FILES))); \
        BAR=$$(seq -s= $$(($$PROGRESS / 5)) | sed 's/[0-9]//g'); \
        printf "\rCompiling project[%-20s] %d%%" $$BAR $$PROGRESS; \
    fi
endef


all : $(NAME)


$(OBJ_DIR)/%.o: $(D_SRCS)%.c | $(OBJ_DIR)
	@$(CC) $(CCFLAG) -I/includes -o $@ -c $<

$(BONUS_OBJ_DIR)/%.o: $(D_BONUS_SRCS)%.c | $(BONUS_OBJ_DIR)
	@$(CC) $(CCFLAG) -I/includes -o $@ -c $<

# Create obj directory if it doesn't exist
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(BONUS_OBJ_DIR):
	@mkdir -p $(BONUS_OBJ_DIR)

$(NAME) : $(OBJECT)
	@$(LOGO)
	$(call progress_bar)
	@$(CC) $(CCFLAG) -o $(NAME) $(OBJECT)
	@echo "\n$(SUCCESS_COLOR)$(NAME) - Compiled with Success"

$(BONUS): $(BONUS_OBJECT)
	@$(LOGO)
	$(call progress_bar)
	@$(CC) $(CCFLAG) -o $(BONUS) $(BONUS_OBJECT)
	@echo "$(SUCCESS_COLOR)$(BONUS) - Bonus Compiled with Success"

bonus: $(BONUS)

clean :
	@echo "$(SUCCESS_COLOR)$(NAME) - Cleaned with Success"
	@/bin/rm -rf $(OBJ_DIR)
	@/bin/rm -rf $(BONUS_OBJ_DIR)

fclean : clean
	@rm -rf ./$(NAME)
	@rm -rf ./$(BONUS)
	@echo "$(SUCCESS_COLOR)$(NAME) - FCleaned with Success"

re : fclean all

.PHONY: all clean fclean re bonus
