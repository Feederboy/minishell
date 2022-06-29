# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mguerra <mguerra@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/06 23:40:58 by mguerra           #+#    #+#              #
#    Updated: 2022/06/29 01:16:59 by mguerra          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRC_DIR = src
OBJ_DIR = obj
SRC = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/*/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))
DEP = $(OBJ:.o=.d)
CC = clang
C_FLAGS = -Wall -Wextra -Werror -g3 -MMD
INCLUDES = -I includes/

LIB_DIR = ./lib

LIBFT_DIR = $(LIB_DIR)/libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_INC = -L$(LIBFT_DIR) -lft

.PHONY: all
all: $(NAME)

-include $(DEP)
obj/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(C_FLAGS) $(INCLUDES) -O3 -c $< -o $@

$(NAME): $(LIBFT)  $(OBJ)
	$(CC) $(C_FLAGS) $(INCLUDES) $(OBJ) -o $(NAME) $(LIBFT_INC) -lreadline

$(LIBFT):
	@make -sC $(LIBFT_DIR)
	@echo LIBFT: COMPILED

test:
	echo $(OBJ)

.PHONY: clean
clean:
	rm -rf obj/

.PHONY: fclean
fclean: clean
	rm -f $(NAME)
	# @make fclean -sC $(LIBFT_DIR)

.PHONY: re
re: fclean all

