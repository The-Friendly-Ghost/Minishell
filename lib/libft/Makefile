# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: pniezen <pniezen@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2022/03/08 13:54:34 by pniezen       #+#    #+#                  #
#    Updated: 2022/11/18 11:53:54 by cpost         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

SRC_PATH = ./src/
OBJ_PATH = ./obj/
INC_PATH = ./include/

NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC_NAME = $(shell ls $(SRC_PATH))

OBJ_NAME = $(SRC_NAME:.c=.o)

OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))

BOLD = \033[1m
GREEN = \033[32;1m
RED	= \033[31;1m
YELLOW	= \033[33;1m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME) && printf "$(YELLOW)$(BOLD)\rBuild $(NAME)\r\e[35C[OK]\n$(RESET)"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c ./include/libft.h
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $< && printf "$(GREEN)$(BOLD)\rCompiling: $(notdir $<)\r\e[35C[OK]\n$(RESET)"

clean:
	@rm -f $(OBJ)
	@rm -rf $(OBJ_PATH)
	@echo "$(RED)Cleaning libft$(RESET)"

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all
