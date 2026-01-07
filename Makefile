# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aandreo <aandreo@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/11 09:39:00 by aandreo           #+#    #+#              #
#    Updated: 2026/01/03 07:40:09 by aandreo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME = philo

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread --fsanitize=address -g
RM = rm -f

# Directories
SRC_DIR = srcs
OBJ_DIR = obj
INC_DIR = include

# Source files
SRCS = 	main.c \
		parsing.c \
		routine.c \
		monitoring.c \
		philos_process.c \
		utils/atol.c \
		utils/time_utils.c \
		utils/routine_utils.c \
		utils/cleanup.c \

# Add src/ prefix to sources
SRC = $(addprefix $(SRC_DIR)/, $(SRCS))

# Object files
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Include flag
INCLUDES = -I$(INC_DIR)

# Colors for output
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

# Rules
all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) compiled successfully!$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "$(GREEN)✓ Compiled: $<$(RESET)"

clean:
	@$(RM) -r $(OBJ_DIR)
	@echo "$(RED)✗ Object files removed$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)✗ $(NAME) removed$(RESET)"

re: fclean all

.PHONY: all clean fclean re
