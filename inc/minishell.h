/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 20:37:51 by lsuardi           #+#    #+#             */
/*   Updated: 2021/04/03 19:03:55 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <signal.h>
# include <fcntl.h>
# include <curses.h>
# include <term.h>
# include <termios.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include <limits.h>
# include <stdbool.h>


/*
** My Libraries
*/
# include <get_next_line.h>
# include <libft.h>
# include <list.h>
# include <garbage.h>

# define CMD_COUNT 7

# ifndef CDIR_BUFFER_SIZE
#  define CDIR_BUFFER_SIZE 32
# endif

# define _KEY_UP 4283163
# define _KEY_DOWN 4348699
# define _KEY_LEFT 4479771
# define _KEY_RIGHT 4414235
# define _KEY_ESC 27
# define _KEY_ENTER 10
# define _KEY_DELETE 127

/*
**	Global struct containing the environment variables and a boolean used for
**	CTRL-C, as well as the termios backup struct and the command history
*/
extern struct	s_globaldata
{
	bool			sigint;
	struct termios	term_backup;
	t_list			*history;
	char			*history_path;
	struct	s_env
	{
		int		count;
		char	*data[];
	}	*env;
}	g_global_data;

/*
**	All builtin function are prototyped
**	`int fun(int argc, char **argv, char **envp);`
*/
typedef int		(*t_builtin_fun)(int, char **, char **);

/*
**	Structure used before sending the input to the program to manage command
**	history and cursor motion, containing:
**		char	*in: the actual input
**		int		index: the new cursor index
**		int		prev_index: the old cursor index (before pressing the last key)
**		t_list	*hist: is a pointer to the last command in the command history
**		int		prev_len: the previous length of the string (before pressing the
**		last key)
*/
typedef struct	s_input
{
	char		*in;
	int			index;
	int			prev_index;
	t_list		*hist;
	int			prev_len;
}	t_input;


/*
**	WORK IN PROGRESS (Parsing)
*/
typedef struct	s_cmd
{
	bool		pipe;
	bool		redirect_in;
	bool		redirect_out;
	bool		redirect_out2;
	char		*in;
	t_list		*out;
	int 		argc;
	char		*argv[];
}	t_cmd;

/*
**	Struct containing all the termcaps necessary for the project.
*/
typedef struct	s_term
{
	char		*le;
	char		*ri;
	char		*ile;
	char		*ks;
}	t_term;

/*
**	Big main structure containing all the data we need for the project.
*/
typedef struct			s_shell
{
	t_term				tcaps;
	char				*executable_name;
	char				*cmd_list[CMD_COUNT];
	t_builtin_fun		builtin_fct_list[CMD_COUNT];
}	t_shell;

/*
**	built-ins
*/
int		builtin_cd(int, char **, char **);
int		builtin_echo(int, char **, char **);
int		builtin_env(int, char **, char **);
int		builtin_exit(int, char **, char **);
int		builtin_export(int, char **, char **);
int		builtin_pwd(int, char **, char **);
int		builtin_unset(int, char **, char **);

/*
**	error.c
*/
int		minishell_error(void);
int		command_error(char *command);
int		syntax_error(char *unexpected_token);

/*
**	sig_handling.c
*/
void	int_handler(int);
void	abort_handler(int);

/*
**	minishell_setup.c
*/
void	minishell_clear(void *data);
void	minishell_init(t_shell *, const char *);
sig_t	setup_signal(void);
int		minishell_setup(t_shell *, char **);

/*
**	history.c
*/
int		get_history(void);
int		save_history(void);

/*
**	key_process_0.c
*/
int		process_key_print(t_input *, int);
int		process_key_del(t_input *);
int		process_key_left(const t_term *, t_input *);
int		process_key_right(const t_term *, t_input *);
int		process_key_hist(const t_list *, t_input *, int);

/*
**	key_process_1.c
*/
int		reset_input(t_input *, const t_list *);
int		key_hist_block(void);
int		update_input(const t_term *, t_input *);

/*
**	minishell_env.c
*/
int		ft_addenv(const char *name, const char *value);
int 	ft_delenv(const char *name);
char	*ft_getenv(const char *name);
int		ft_setenv(const char *name, const char *value);
void	ft_clearenv(void);
void	ft_printenv(void);

/*
**	minishell_exit.c
*/
void	minishell_exit(int ret);

/*
**	parsing
*/
char	**lexer(char *input_str);
t_cmd	**parser(char **tokens);

#endif
