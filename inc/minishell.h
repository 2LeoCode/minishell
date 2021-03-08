/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 20:37:51 by lsuardi           #+#    #+#             */
/*   Updated: 2021/03/08 18:43:14 by lsuardi          ###   ########.fr       */
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
# include <sys/stat.h>
# include <sys/types.h>
# include <limits.h>
# include <envlist.h>
# include <get_next_line.h>

# define CMD_COUNT 7

# ifndef CDIR_BUFFER_SIZE
#  define CDIR_BUFFER_SIZE 32
# endif

# define NENV 0
# define ENV 1

typedef struct s_varlist	t_varlist;

typedef struct				s_shell_varlist
{
	t_varlist *				exp;
	t_varlist *				nexp;
}							t_shell_varlist;

typedef int					(*builtin_function)
(int, char ** , char **);

typedef struct				s_shell
{
	t_varlist *				var;
	char *					executable_name;
	char *					pipe_output;
	char *					prev_input;
	char *					cmd_list[CMD_COUNT];
	builtin_function		builtin_fct_list[CMD_COUNT];
}							t_shell;

extern int					g_exit_builtins;
extern char **				g_env;
extern char **				g_var;

/*
** error.c
*/
int							exit_error(void);

/*
** sig_handling.c
*/
void						int_handler(int);

/*
** utils_0.c
*/
void *						destroy(void **);
void						swap_ptr(void **, void **);
void						swap_int(int *, int *);
int							ft_isspace(char c);
long long					ft_atoll(const char *);

/*
** str_utils_0.c
*/
size_t						ft_strlen(const char *);
int							ft_strcmp(const char *, const char *);
int							ft_strncmp(const char *, const char *, size_t);
char *						ft_strncpy(char *, const char *, size_t);
char *						ft_strdup(const char *);

/*
** str_utils_1.c
*/
char *						ft_strncat(char *, const char *, size_t);
char *						ft_strjoin(const char *, const char *, char);
char *						ft_strchr(const char *, int);
char *						str_replace_chr(char *, int, int);
char *						str_replace(char **, const char *, const char *);

/*
** str_utils_2.c
*/
size_t						number_of_occurences(const char *, const char *);

/*
** ft_split.c
*/
char **						ft_split(const char *, const char *);

/*
** minishell_setup.c
*/
void						minishell_init(t_shell *, const char *);
int							minishell_setup(t_shell *, const char **);


/*
** global_0.c
*/
void *						destroy_global(int);
int							varlist_update_global(const t_varlist *);
int							varlist_update_local(t_varlist **);

/*
** global_1.c
*/
void *						update_global_env(const t_varlist *);
void *						update_global_var(const t_varlist *);

#endif
