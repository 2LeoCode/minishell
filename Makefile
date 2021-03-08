# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/19 23:12:58 by lsuardi           #+#    #+#              #
#    Updated: 2021/03/02 19:55:11 by lsuardi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL =		/bin/sh
.SUFFIXES =	.c .h .o

NAME =		minishell

SRCD =		src
INCD =		inc
OBJD =		.obj

SRC =		$(addsuffix $(word 1, $(.SUFFIXES)),\
			main\
			error\
			sig_handling\
			varlist_0\
			varlist_1\
			varlist_2\
			get_next_line\
			get_next_line_utils\
			utils_0\
			str_utils_0\
			str_utils_1\
			$(addprefix builtin_,\
			cd\
			echo\
			env\
			exit\
			export\
			pwd\
			unset))
INC =		$(addsuffix $(word 2, $(.SUFFIXES)),\
			minishell\
			get_next_line\
			varlist)
OBJ =		$(SRC:$(word 1, $(.SUFFIXES))=$(word 3, $(.SUFFIXES)))

CC =		gcc
CFLAGS =	-Wall\
			-Werror\
			-Wextra\
			-I $(INCD)

COUNT =		$(shell cat file.count 2>/dev/null)

ifeq ($(COUNT),)
all:
	@echo $(words $(SRC)) > file.count && $(MAKE) -n | grep $(CC) | wc -l | tr -d ' ' > tmp.txt && rm -f file.count && echo $$(($$(cat tmp.txt) - 1)) > file.count && rm -f tmp.txt && ./make/remake.sh
else
all: $(NAME)
endif

$(NAME): $(addprefix $(OBJD)/, $(OBJ)) | $(addprefix $(INCD)/, $(INC))
	@rm -f file.count && $(CC) $(CFLAGS) $^ -o $@ && echo '\r\033[2KCompiling [100%]'

$(OBJD):
	@mkdir $@

$(OBJD)/%$(word 3, $(.SUFFIXES)): $(SRCD)/%$(word 1, $(.SUFFIXES)) | $(OBJD)
	@./make/prc.sh 2>/dev/null && $(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJD)

fclean: clean
	@rm -f $(NAME)

re: fclean all
