# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: upopee <upopee@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/15 11:05:28 by upopee            #+#    #+#              #
#    Updated: 2018/02/08 06:21:21 by upopee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -- VARIABLES --

# Name
NAME = lem-in

# Compiler
CC = gcc

# Flags
CFLAGS = -Wall -Wextra -Wall $(INCLUDES) -g
LFLAGS =  -lft -L $(LIB_DIR)

# Library paths
LIB_DIR = ./libft
LIB_INCLUDES_DIR = $(LIB_DIR)

# Sources paths
VPATH = sources
INCLUDES_DIR = includes

# Includes paths
INCLUDES = -I $(INCLUDES_DIR) -I $(LIB_INCLUDES_DIR)

# Sources files
FILES =		main_lem_in \
			struct_utils \
			parsing_core \
			parsing_utils \

SOURCES = $(patsubst %,$(SRC_DIR)/%,$(FILES:=.c))
SRC_DIR = sources

# Objects files
OBJECTS = $(patsubst %,$(OBJ_DIR)/%,$(FILES:=.o))
OBJ_DIR = .objects

# -- RULES --

all: prep $(NAME)

$(NAME): lib
	printf "> \e[31;33;1m$(NAME)\e[0m : \e[32mCreating objects \e[0m "
	make obj
	printf "\n"
	printf "> \e[31;33;1m$(NAME)\e[0m : \e[32mCreating binary\e[0m "
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJECTS) -o $(NAME)
	printf "\t\t\e[37;1m[\e[32;1mDONE\e[0m\e[37;1m]\e[0m\n"

obj: $(OBJECTS)
	echo >> /dev/null

$(OBJ_DIR)/%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)
	printf "\e[32m.\e[0m"

lib:
	make -C $(LIB_DIR)

clean:
	printf "> \e[31;33;1m$(NAME)\e[0m : \e[31mDeleting objects\e[0m "
	rm -rf $(OBJ_DIR)
	printf "\t\t\e[37;1m[\e[31;1mX\e[0m\e[37;1m]\e[0m\n"
	make -C $(LIB_DIR) $@

fclean: clean
	printf "> \e[31;33;1m$(NAME)\e[0m : \e[31mDeleting binary\e[0m "
	rm -f $(NAME)
	printf "\t\t\e[37;1m[\e[31;1mX\e[0m\e[37;1m]\e[0m\n"
	make -C $(LIB_DIR) $@

re: fclean all

prep:
	mkdir -p $(OBJ_DIR)

sandwich: re
	make clean
	echo "Sandwich ready !"
# This rule allow the library build process to complete even if there are
# files named 'all, clean, fclean, re' in the working directory


.PHONY: all obj lib clean fclean re sandwich prep debug

.SILENT: all obj lib clean fclean re sandwich prep debug $(NAME) $(OBJECTS)
