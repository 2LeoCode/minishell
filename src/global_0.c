/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 00:32:01 by lsuardi           #+#    #+#             */
/*   Updated: 2021/03/08 18:41:30 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		g_exit_builtins;
char **	g_env;
char **	g_var;

g_exit_builtins = 0;
g_env = NULL;
g_var = NULL;

void *	destroy_global(int env)
{
	char **	it;

	if (env)
	{
		if ((it = g_env - 1) == (void*)-1)
			return (NULL);
		while (*(++it))
			free(*it);
		free(g_env);
		g_env = NULL;
	}
	else
	{
		if ((it = g_var - 1) == (void*)-1)
			return (NULL);
		while (*(++it))
			free(*it);
		free(g_var);
		g_var = NULL;
	}
	return (NULL);
}

int		varlist_update_global(const t_varlist * varlist)
{
	update_global_env(varlist);
	if (!g_env)
		return (-1);
	update_global_var(varlist);
	return (-1 * !g_var);
}

static int	get_local_missing_var(t_varlist ** missing, const t_varlist * list)
{
	char **		it;
	t_varlist * begin;

	begin = list;
	it = g_var;
	while (*(++it))
	{
		list = begin;
		while (list)
		{
			if (!ft_strcmp(*it, list->var))
				break ;
			list = list->next;
		}
		if (!list)
			if (varlist_push_raw(missing, *it, 0))
				return ((int)varlist_clear(missing) - 1);
	}
	return (0);
}

static int	get_local_missing_env(t_varlist ** missing, const t_varlist * list)
{
	char **		it;
	t_varlist * begin;

	begin = list;
	it = g_env;
	while (*(++it))
	{
		list = begin;
		while (list)
		{
			if (!ft_strcmp(*it, list->var))
				break ;
			list = list->next;
		}
		if (!list)
			if (varlist_push_raw(missing, *it, 1))
				return ((int)varlist_clear(missing) - 1);
	}
	return (0);
}

int			varlist_update_local(t_varlist ** varlist_ptr)
{
	t_varlist *	missing;

	it = g_var - 1;
	missing = NULL;
	if (get_local_missing_var(&missing, *varlist_ptr)
	|| get_local_missing_env(&missing, *varlist_ptr))
		return (-1);
	while (missing)
	{
		if (varlist_set_raw(varlist_ptr, missing->var))
			return ((int)varlist_clear(&missing) - 1);
		missing = missing->next;
	}
	return ((int)varlist_clear(&missing));
}
