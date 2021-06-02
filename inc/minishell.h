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



# define NENV 0
# define ENV 1

#define _KEY_UP 16758
#define _KEY_DOWN 17014
#define _KEY_LEFT 17526
#define _KEY_RIGHT 17270
#define _KEY_ESC 27
#define _KEY_ENTER 10
#define _KEY_DELETE 127

struct	s_env
{
	int		count;
	char	*data[];
} env;

typedef int		(*t_builtin_fun)(int, char **, char **);

typedef enum	e_token_type
{
	token_end,
	token_text,
	token_semicolon,
	token_pipe,
	token_arrow_left,
	token_arrow_right,
	token_double_arrow_right,
	token_single_quote,
	token_double_quote
}	t_token_type;

typedef struct	s_token
{
	char			*token_ptr;
	t_token_type	token_type;
}	t_token;

typedef struct	s_input
{
	char		*in;
	int			index;
	int			prev_index;
	t_list		*hist;
	t_list		*prev_hist;
	int			prev_len;
}	t_input;

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

typedef struct	s_term
{
	char		*le;
	char		*ri;
	char		*ile;
	char		*ks;
}	t_term;

typedef struct			s_shell
{
	struct termios		term_shell;
	struct termios		term_backup;
	t_term				tcaps;
	t_list				*history;
	int					history_index;
	char				*history_path;
	char				*executable_name;
	char				*cmd_list[CMD_COUNT];
	t_builtin_fun		builtin_fct_list[CMD_COUNT];
}	t_shell;

/*
** built-ins
*/
int		builtin_cd(int, char **, char **);
int		builtin_echo(int, char **, char **);
int		builtin_env(int, char **, char **);
int		builtin_exit(int, char **, char **);
int		builtin_export(int, char **, char **);
int		builtin_pwd(int, char **, char **);
int		builtin_unset(int, char **, char **);

/*
** error.c
*/
int		minishell_error(void);

/*
** sig_handling.c
*/
void	int_handler(int);
void	abort_handler(int);

/*
** minishell_setup.c
*/
void	*minishell_clear(t_shell *);
void	minishell_init(t_shell *, const char *);
int		minishell_setup(t_shell *, const char **);

/*
** history.c
*/
int		get_history(t_shell *);
int		save_history(t_shell *);

/*
** key_process_0.c
*/
int		process_key_print(t_input *, int);
int		process_key_del(t_input *);
int		process_key_left(const t_term *, t_input *);
int		process_key_right(const t_term *, t_input *);
int		process_key_hist(const t_list *, t_input *, int);

/*
** key_process_1.c
*/
int		reset_input(t_input *, const t_list *);
int		key_hist_block(void);
int		update_input(const t_term *, t_input *);

#endif
