/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varlist.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 22:35:22 by lsuardi           #+#    #+#             */
/*   Updated: 2021/03/07 19:29:10 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef varlist_H
# define varlist_H

# define VARLIST_CMP_NAME &varlist_cmp_name
# define VARLIST_CMP_DATA &varlist_cmp_data
# define VARLIST_CMP_RAW &ft_strcmp

# include <minishell.h>

typedef struct			s_varlist
{
	char *				var;
	int					env;
	struct s_varlist *	next;
}						t_varlist;

t_varlist *				varlist_new(const char *, const char *, int);
t_varlist *				varlist_new_raw(const char *, int);
int						varlist_push(t_varlist **, const char *, const char *,
int);
int						varlist_push_raw(t_varlist **, const char *, int);
char *					varlist_get(const t_varlist *, const char *);
int						varlist_set(t_varlist **, const char *, const char *,
int);
int						varlist_set_raw(t_varlist **, const char *, int);
int						varlist_export(t_varlist **, const char *);
int						varlist_copy(t_varlist **, const t_varlist *,
const char *);
char **					varlist_get_env_array(const t_varlist *);
char **					varlist_get_nonenv_array(const t_varlist *);
t_varlist *				varlist_last(const t_varlist *);
int						varlist_rm(t_varlist **, const t_varlist *);
void					varlist_sort(t_varlist *, int (*)(const char *,
const char *));
int						varlist_rm_if(t_varlist **, const char *,
int (*)(const char *, const char *));
int						varlist_cmp_name(const char * env, const char * name);
int						varlist_cmp_data(const char * env, const char * data);
size_t					varlist_size(const t_varlist *);
void *					varlist_clear(t_varlist **);

#endif
