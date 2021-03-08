/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varlist_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 22:46:29 by lsuardi           #+#    #+#             */
/*   Updated: 2021/03/04 20:18:55 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <varlist.h>

t_varlist *	varlist_new(const char * name, const char * value, int env)
{
	char *		new_var;
	t_varlist *	new_list;

	if (!(new_list = malloc(sizeof(t_varlist))))
		return (NULL);
	if (!*value)
		new_var = ft_strjoin(name, "\'\'", '=');
	else
		new_var = ft_strjoin(name, value, '=');
	new_list->next = NULL;
	new_list->var = new_var;
	new_list->env = env;
	if (!new_var)
		destroy((void**)&new_list);
	return (new_list);
}

t_varlist *	varlist_last(const t_varlist * list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return ((t_varlist*)list);
}

int			varlist_push(t_varlist ** list_ptr, const char * name, const char * value, int env)
{
	t_varlist * new_var;

	if (!(new_var = varlist_new(name, value, env)))
		return (-1);
	if (*list_ptr)
		varlist_last(*list_ptr)->next = new_var;
	else
		*list_ptr = new_var;
	return (0);
}

char *		varlist_get(const t_varlist * list, const char * var)
{
	size_t n;

	n = ft_strlen(var);
	while (list)
		if (!ft_strncmp(var, list->var, n))
			return (ft_strdup(ft_strcmp(var + n, "=\'\'") ? (var + n + 1) : ""));
	return (NULL);
}

int			varlist_set(t_varlist ** list_ptr, const char * var, const char * value, int env)
{
	if (varlist_get(*list_ptr, var))
		varlist_rm_name(list_ptr, var);
	return (varlist_push(list_ptr, var, value, env));
}
