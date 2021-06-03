SHELL =		/bin/sh
NAME =		minishell

.SUFFIXES =	.c .o .h

SRCDIR =	src
INCDIR =	inc
LIBDIR =	lib
OBJDIR =	.obj

SRC =		$(addsuffix $(word 1, $(.SUFFIXES)),\
			$(addprefix builtins/builtin_,\
			cd\
			echo\
			env\
			exit\
			export\
			pwd\
			unset)\
			$(addprefix key_processing/key_process_,\
			0\
			1)\
			error\
			history\
			main\
			minishell_env\
			minishell_clear\
			minishell_parser\
			minishell_setup\
			sig_handling)
INC =		$(addsuffix $(word 3, $(.SUFFIXES)),\
			libft\
			get_next_line\
			list\
			garbage\
			minishell)
LIB	 =		ft\
            list\
            gnl\
            gb\
            ncurses
OBJ =		$(SRC:$(word 1, $(.SUFFIXES))=$(word 2, $(.SUFFIXES)))

CC =		gcc
CFLAGS =	-Wall -Wextra -Werror -I $(INCDIR)
LCFLAGS =	$(addprefix -L, $(LIBDIR)) $(addprefix -l, $(LIB))

####    COLORS    ####
KNRM =		\x1B[0m
KRED =		\x1B[31m
KGRN =		\x1B[32m
KYEL =		\x1B[33m
KBLU =		\x1B[34m
KMAG =		\x1B[35m
KCYN =		\x1B[36m
KWHT =		\x1B[37m
######################

all: libraries $(OBJDIR) $(NAME)
	@printf "$(KGRN)\`$(NAME)\` is up to date.\n"

$(OBJDIR):
	@printf "$(KYEL)➤ "
	mkdir $@
	@printf "➤ "
	mkdir $@/builtins $@/key_processing
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
	@printf "$(KCYN)➤ "
	$(MAKE) -C $(LIBDIR)/libgb
	@printf "$(KYEL)➤ "
	cp $(LIBDIR)/get_next_line_ultimate/libgnl.a $(LIBDIR)/libft_ultimate/libft.a $(LIBDIR)/liblist_ultimate/liblist.a $(LIBDIR)/libgb/libgb.a $(LIBDIR)/
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
	@printf "$(KRED)➤ "
	$(MAKE) fclean -C $(LIBDIR)/libgb

fclean: clean
	@printf "$(KRED)➤ "
	rm -f $(NAME)
	@printf "$(KNRM)"

re: fclean all
