# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: pniezen <pniezen@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2022/08/24 13:48:16 by pniezen       #+#    #+#                  #
#    Updated: 2022/11/28 11:34:38 by pniezen       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

BREW_DIR = $(shell brew --prefix)
LIBREADLINE = $(BREW_DIR)/opt/readline/lib

SRC_PATH = src
OBJ_PATH = obj
INC_PATH = include lib/libft/include $(BREW_DIR)/opt/readline/include 

LIBFT_PATH = lib/libft/

NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=address

SRC = $(shell find $(SRC_PATH) -type f -name '*.c')

OBJ = $(addprefix $(OBJ_PATH)/,$(SRC:.c=.o))

INC = $(addprefix -I,$(INC_PATH))
LIB = -L$(LIBREADLINE) -lreadline  $(LIBFT_PATH)libft.a

BOLD = \033[1m
GREEN = \033[32;1m
RED	= \033[31;1m
YELLOW	= \033[33;1m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIBFT_PATH)
	@$(CC) $(CFLAGS) $(LIB) $(OBJ) $(INC) -o $(NAME) && printf "$(YELLOW)$(BOLD)\rBuild $(NAME)\r\e[35C[OK]\n$(RESET)"

$(OBJ_PATH)/%.o: %.c include/minishell.h
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -o $@ -c $< $(INC) && printf "$(GREEN)$(BOLD)\rCompiling: $(notdir $<)\r\e[35C[OK]\n$(RESET)"

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
