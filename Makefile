# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mguerra <mguerra@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/06 23:40:58 by mguerra           #+#    #+#              #
#    Updated: 2022/06/29 10:32:02 by mguerra          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRC_DIR = src
OBJ_DIR = obj
SRC = src/exec/builtin.c src/exec/pipe.c src/exec/execution.c \
src/exec/exec_utils2.c src/exec/exec_utils.c src/exit.c src/main.c \
src/builtins/export.c src/builtins/env.c src/builtins/pwd.c src/builtins/echo.c\
src/builtins/unset.c src/builtins/cd.c src/builtins/exit.c \
src/parsing/redirection.c src/parsing/env_utils.c src/parsing/env.c \
src/parsing/command.c src/parsing/prompt.c src/parsing/heredoc.c \
src/parsing/parse.c src/parsing/expand.c src/str_utils.c \
src/signals.c src/utils.c
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

