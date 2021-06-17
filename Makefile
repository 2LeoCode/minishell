OS =		$(shell uname)
SHELL =		/bin/sh
NAME =		minishell

.SUFFIXES =	.c .o .h

SRCDIR =	src
INCDIR =	inc
LIBDIR =	lib
OBJDIR =	.obj



SRC =		$(addsuffix $(word 1, $(.SUFFIXES)),\
			$(addprefix builtins/,\
			builtin_cd\
			builtin_echo\
			builtin_env\
			builtin_exit\
			builtin_export\
			builtin_pwd\
			builtin_unset)\
			$(addprefix key_processing/,\
			key_process_1\
			key_process_2\
			key_process)\
			$(addprefix parsing/,\
			executer_init\
			executer_utils_1\
			executer_utils\
			executer\
			lexer_utils\
			lexer\
			parser_utils_1\
			parser_utils\
			parser_variable\
			parser\
			syntax_checker)\
			$(addprefix setup/,\
			minishell_setup\
			term_setup)\
			main\
			minishell_clear\
			minishell_env\
			minishell_error\
			minishell_exit\
			minishell_history\
			signal_handling)
INC =		$(addsuffix $(word 3, $(.SUFFIXES)),\
			libft\
			get_next_line\
			list\
			minishell)
LIB	 =		ft\
            list\
            gnl\
            ncurses
OBJ =		$(SRC:$(word 1, $(.SUFFIXES))=$(word 2, $(.SUFFIXES)))

CC =		gcc
CFLAGS =	-I $(INCDIR) -Wall -Wextra -Werror -fsanitize=address -g3
LCFLAGS =	$(addprefix -L, $(LIBDIR)) lib/libft.a lib/liblist.a lib/libgnl.a $(addprefix -l, $(LIB))

ifeq ($(OS), Darwin)
	KNRM =		\x1B[0m
	KRED =		\x1B[31m
	KGRN =		\x1B[32m
	KYEL =		\x1B[33m
	KBLU =		\x1B[34m
	KMAG =		\x1B[35m
	KCYN =		\x1B[36m
	KWHT =		\x1B[37m
else
	KNRM =		\e[39m
	KRED =		\e[31m
	KGRN =		\e[32m
	KYEL =		\e[33m
	KBLU =		\e[34m
	KMAG =		\e[35m
	KCYN =		\e[36m
	KWHT =		\e[37m
endif

all: libraries $(OBJDIR) $(NAME)
	@printf "$(KGRN)\`$(NAME)\` is up to date.\n$(KNRM)"

$(OBJDIR):
	@printf "$(KYEL)➤ "
	mkdir $@
	@printf "➤ "
	mkdir $@/builtins $@/key_processing $@/parsing $@/setup
	@printf "$(KNRM)"

$(NAME): $(addprefix $(OBJDIR)/, $(OBJ))
	@printf "$(KCYN)[  Linking  ]\n➤ "
	$(CC) $(CFLAGS) $^ -o $@ $(LCFLAGS)
	@printf "$(KNRM)"

libraries:
	@printf "$(KCYN)[  Building $@  ]\n➤ "
	$(MAKE) -C $(LIBDIR)/get_next_line_ultimate
	@printf "$(KCYN)➤ "
	$(MAKE) -C $(LIBDIR)/libft_ultimate
	@printf "$(KCYN)➤ "
	$(MAKE) -C $(LIBDIR)/liblist_ultimate
	@printf "$(KYEL)➤ "
	cp $(LIBDIR)/get_next_line_ultimate/libgnl.a $(LIBDIR)/libft_ultimate/libft.a $(LIBDIR)/liblist_ultimate/liblist.a $(LIBDIR)/
	@printf "$(KNRM)"

$(OBJDIR)/%$(word 2, $(.SUFFIXES)): $(SRCDIR)/%$(word 1, $(.SUFFIXES)) $(addprefix $(INCDIR)/, $(INC))
	@printf "$(KMAG)[  Compiling  ]\n➤ "
	$(CC) $(CFLAGS) -c $< -o $@
	@printf "$(KNRM)"

clean:
	@printf "$(KRED)➤ "
	rm -rf $(OBJDIR)
	@printf "➤ "
	rm -f $(foreach i, $(LIB), $(LIBDIR)/lib$(i).a)
	@printf "➤ "
	$(MAKE) fclean -C $(LIBDIR)/get_next_line_ultimate
	@printf "$(KRED)➤ "
	$(MAKE) fclean -C $(LIBDIR)/libft_ultimate
	@printf "$(KRED)➤ "
	$(MAKE) fclean -C $(LIBDIR)/liblist_ultimate

fclean: clean
	@printf "$(KRED)➤ "
	rm -f $(NAME)
	@printf "$(KNRM)"

re: fclean all
