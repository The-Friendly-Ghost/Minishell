# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: pniezen <pniezen@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2022/08/16 08:11:25 by pniezen       #+#    #+#                  #
#    Updated: 2022/08/24 11:09:32 by pniezen       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

SRC_PATH = ./src/
OBJ_PATH = ./obj/
INC_PATH = ./include/ ./lib/libft/include/

LIBFT_PATH = ./lib/libft/

NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

SRC_NAME = $(shell ls $(SRC_PATH))

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))
LIB = -lreadline $(LIBFT_PATH)libft.a

BOLD = \033[1m
GREEN = \033[32;1m
RED	= \033[31;1m
YELLOW	= \033[33;1m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIBFT_PATH)
	@$(CC) $(CFLAGS) $(LIB) $(INC) $(OBJ) -o $(NAME) && printf "$(YELLOW)$(BOLD)\rBuild $(NAME)\r\e[35C[OK]\n$(RESET)"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c ./include/minishell.h
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $< && printf "$(GREEN)$(BOLD)\rCompiling: $(notdir $<)\r\e[35C[OK]\n$(RESET)"

run: all
	@./minishell

cleanlib:
	@make -C $(LIBFT_PATH) clean

clean:
	@rm -rf $(OBJ_PATH)
	@echo "$(RED)Cleaning minishell$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: clean, fclean, re, all
