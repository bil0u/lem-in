# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: upopee <upopee@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/15 11:05:28 by upopee            #+#    #+#              #
#    Updated: 2018/02/14 17:24:48 by upopee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -- VARIABLES --

NAME = lem-in
CC = gcc
CFLAGS = -Wall -Werror -Wextra $(INCLUDES) -g
LFLAGS =  -lft -L $(LIB_DIR)
AR = ar -rc
LINK = ar -s
LIBMAKE = make -C
NEW_DIR = mkdir -p
DEL_DIR = rm -rf
DEL_FILE = rm -f

# -- COLORS --

YELLOW_BOLD = \e[31;33;1m
GREEN = \e[32m
GREEN_BOLD = \e[32;1m
RED = \e[31m
RED_BOLD = \e[31;1m
WHITE_BOLD = \e[37;1m
EOC = \e[0m

# -- PATHS --

SRC_DIR = sources
INC_DIR = includes
OBJ_DIR = .objects
LIB_DIR = libft

VPATH = sources
INCLUDES = -I $(INC_DIR) -I $(LIB_DIR)

# -- FILES --

FILES =		main_lem_in \
			struct_utils \
			parsing_core \
			parsing_utils \
			pathfinding_core \
			pathfinding_utils \
			solve \

SOURCES = $(patsubst %,$(SRC_DIR)/%,$(FILES:=.c))
OBJECTS = $(patsubst %,$(OBJ_DIR)/%,$(FILES:=.o))

# -- IMPLICIT RULES --

$(OBJ_DIR)/%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)
	printf "$(GREEN).$(EOC)"


# -- RULES --

all: prep $(NAME)

$(NAME): lib
	printf "> $(YELLOW_BOLD)$(NAME)$(EOC) : $(GREEN)Creating objects$(EOC) "
	make obj
	printf "\n"
	printf "> $(YELLOW_BOLD)$(NAME)$(EOC) : $(GREEN)Creating Library$(EOC) "
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJECTS) -o $(NAME)
	printf "\t$(WHITE_BOLD)[$(GREEN_BOLD)DONE$(WHITE_BOLD)]$(EOC)\n"

obj: $(OBJECTS)
	echo >> /dev/null

lib:
	$(LIBMAKE) $(LIB_DIR)

clean:
	printf "> $(YELLOW_BOLD)$(NAME)$(EOC) : $(RED)Deleting objects$(EOC) "
	$(DEL_DIR) $(OBJ_DIR)
	printf "\t$(WHITE_BOLD)[$(RED_BOLD)X$(WHITE_BOLD)]$(EOC)\n"
	$(LIBMAKE) $(LIB_DIR) $@

fclean: clean
	printf "> $(YELLOW_BOLD)$(NAME)$(EOC) : $(RED)Deleting binary$(EOC) "
	$(DEL_FILE) $(NAME)
	printf "\t$(WHITE_BOLD)[$(RED_BOLD)X$(WHITE_BOLD)]$(EOC)\n"
	$(LIBMAKE) $(LIB_DIR) $@

re: fclean all

prep:
	$(NEW_DIR) $(OBJ_DIR)

.PHONY: all obj lib clean fclean re sandwich prep debug

.SILENT: all obj lib clean fclean re sandwich prep debug $(NAME) $(OBJECTS)
