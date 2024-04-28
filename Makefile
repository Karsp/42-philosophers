# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: daviles- <daviles-@student.42madrid.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/05 16:56:46 by daviles-          #+#    #+#              #
#    Updated: 2024/01/05 16:56:48 by daviles-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# MAKEFILE CON BARRA Y COMPILANDO TO LO QUE SE LE PONE POR DELANTE
# Colors
COLOR_RESET = \033[0m
COLOR_RED = \033[0;31m
COLOR_RED_N = \033[1;31m
COLOR_GREEN = \033[0;32m
COLOR_GREEN_N = \033[1;32m
COLOR_YELLOW = \033[0;33m
COLOR_YELLOW_N = \033[1;33m
COLOR_BLUE = \033[0;34m
COLOR_BLUE_N = \033[1;34m
COLOR_PURPLE = \033[0;35m
COLOR_PURPLE_N = \033[1;35m

NAME = philo
CC = gcc
CFLAGS = -Werror -Wextra -Wall -g3 -fsanitize=address 
CFLAGS += -O3
CFLAGS += -I inc
LDFLAG = -pthread

SRC_DIR = src
OBJ_DIR = obj
INCLUDE = include/philo.h
SRC = $(shell find $(SRC_DIR) -name '*.c')
OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))
RM = rm -f

CHANGES_MADE = 0
CHARS_LEN := 0
CHARS := 0
progress := 4

all: $(NAME)
		@if [ "$(CHANGES_MADE)" -eq "0" ]; then \
				echo "$(COLOR_RED)No hay cambios para hacer. $(COLOR_RESET)"; \
		fi
		$(call print_progress)
		$(eval progress := 50)
		$(call print_progress)
		$(eval progress := 100)
		$(call print_progress)
		@echo ""

$(NAME):$(OBJ) $(LIBFT) $(INCLUDE)
		@$(CC) $(CFLAGS) $(OBJ) $(LDFLAG) $(LIBFT) -o $(NAME)
		@$(eval CHANGES_MADE=1)

$(LIBFT):
		@make -C $(LIBFT_DIR) > /dev/null

define print_progress
		@printf "\r$(COLOR_GREEN)[$(COLOR_GREEN_N) %d%%%*.*s $(COLOR_GREEN)] $(COLOR_PURPLE_N)Minishell $(COLOR_PURPLE)Compiling 🛠️$(COLOR_RESET)" $(progress) $(CHARS_LEN) $(CHARS)
endef

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
		@mkdir -p $(dir $@)
		@$(CC) $(CFLAGS) -c -o $@ $<
		$(eval progress=$(shell echo $$(($(progress) + 1))))
		$(call print_progress)
# @echo "$(COLOR_BLUE) Created! 😸 $(COLOR_RESET)"

clean:
		@rm -rf $(OBJ_DIR)  > /dev/null

fclean: clean
		@rm -f $(NAME)
		@echo "$(COLOR_RED_N) Cleaned all! 🧹 $(COLOR_RESET)"

normi:
		norminette

re: fclean all

.PHONY: all, clean, fclean, re