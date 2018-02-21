# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: upopee <upopee@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/15 11:05:28 by upopee            #+#    #+#              #
#    Updated: 2018/02/21 18:39:28 by upopee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -- PROJECT VARIABLES & COMMANDS --

NAME =		lem-in
CC =		gcc
CFLAGS =	-Wall -Werror -Wextra
CPPFLAGS =	-I $(INC_DIR) -I $(LIBFT_INC)

SHELL =		/bin/bash
LDMAKE =	make -C
MKDIR =		mkdir -p
RMDIR =		rm -rf
RM =		rm -f
NORM =		norminette

# -- LIBRARIES --

LDLIBS =	-lft
LDFLAGS =	-Llibft

LIBFT_DIR =	libft
LIBFT_LIB =	$(LIBFT_DIR)/libft.a
LIBFT_INC =	$(LIBFT_DIR)

# -- PATHS NAMES --

SRC_DIR =	sources
INC_DIR =	includes
OBJ_DIR =	.objects

# -- PROJECT FILES --

C_FILES =	main_lem_in \
			struct_utils \
			print_utils \
			parsing_core \
			parsing_utils \
			pathfinding_core \
			pathfinding_utils \
			solve \

H_FILES =	lem_in \
			parsing \
			pathfinding \
			struct_utils \
			print_utils \

OBJECTS = $(patsubst %,$(OBJ_DIR)/%,$(C_FILES:=.o))
INCLUDES = $(patsubst %,$(INC_DIR)/%,$(H_FILES:=.h))

# -- IMPLICIT RULES  / LINKING --

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDES)

	@$(eval DONE=$(shell echo $$(($(INDEX)*20/$(NB)))))
	@$(eval PERCENT=$(shell echo $$(($(INDEX)*100/$(NB)))))
	@$(eval TO_DO=$(shell echo $$((20-$(INDEX)*20/$(NB) - 1))))
	@$(eval COLOR=$(shell list=(160 196 202 208 215 221 226 227 190 154 118 82 46); index=$$(($(PERCENT) * $${#list[@]} / 100)); echo "$${list[$$index]}"))
	@printf "\r> $(YELLOW)$(NAME)$(EOC) : Creating binary...  %2d%% $(CNO)[`printf '#%.0s' {0..$(DONE)}`%*s]$(YELLOW)%*.*s$(EOC)$(ERASELN)" $(PERCENT) $(COLOR) $(TO_DO) "" $(DELTA) $(DELTA) "$(shell echo "$@" | sed 's/^.*\///')"
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	@$(eval INDEX=$(shell echo $$(($(INDEX)+1))))

# -- RULES --

all: $(NAME)

$(NAME): $(LIBFT_LIB) $(OBJ_DIR) $(OBJECTS) Makefile
	@$(CC) $(LDLIBS) $(LDFLAGS) $(OBJECTS) -o $@
	@printf "\r$(ERASELN)> $(YELLOW)$(NAME)$(EOC) : Binary created !\t$(GREEN_B)✓$(EOC)\n"

$(LIBFT_LIB):
	@$(LDMAKE) $(LIBFT_DIR)

$(OBJ_DIR):
	@$(MKDIR) $(OBJ_DIR)

clean: libclean
	@if [ -e $(OBJ_DIR) ]; \
	then \
		$(RMDIR) $(OBJ_DIR); \
		printf "> $(YELLOW)$(NAME)$(EOC) : Objects deleted\t$(RED_B)✗$(EOC)\n"; \
	fi;

libclean:
	@$(LDMAKE) $(LIBFT_DIR) clean

fclean: clean libfclean
	@if [ -e $(NAME) ]; \
	then \
		$(RM) $(NAME); \
		printf "> $(YELLOW)$(NAME)$(EOC) : Binary deleted\t$(RED_B)✗$(EOC)\n"; \
	fi;

libfclean:
	@$(LDMAKE) $(LIBFT_DIR) fclean

re: fclean all

libre: libfclean $(LIBFT_LIB)

norm:
	@$(NORM) $(SRC_DIR)
	@$(NORM) $(INC_DIR)

libnorm:
	@$(NORM) $(LIB_DIR)

.PHONY: all clean libclean fclean libfclean re libre norm libnorm

# -- DISPLAY --

LEN_NAME =	`printf "%s" $(NAME) |wc -c`
DELTA =		$$(echo "$$(tput cols)-51-$(LEN_NAME)"|bc)
NB =		$(words $(C_FILES))
INDEX=		0

ERASELN =	\033[K
CNO =		\033[38;5;%dm

YELLOW =	\e[31;33m
YELLOW_B =	\e[31;33;1m
GREEN =		\e[32m
GREEN_B =	\e[32;1m
RED =		\e[31m
RED_B =		\e[31;1m
WHITE =		\e[37m
WHITE_B =	\e[37;1m
EOC =		\e[0m
