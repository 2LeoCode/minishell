/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varlist_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 21:38:42 by lsuardi           #+#    #+#             */
/*   Updated: 2021/03/04 22:29:45 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <varlist.h>

t_varlist *	varlist_new_raw(const char * raw_data, int env)
{
	t_varlist * list;
	char *		parse;

	parse = (char*)raw_data;
	if (!(list = malloc(sizeof(t_varlist))))
		return (NULL);
	while (*(parse++))
		if (*parse == '=')
		{
			if ((!*(++parse) && !(list->var = ft_strjoin(raw_data, "\'\'", 0)))
			|| (*parse && !(list->var = ft_strdup(raw_data))))
				return (destroy((void**)&list));
			list->next = NULL;
			return (list);
		}
	if (!(list->var = ft_strjoin(raw_data, "\'\'", '=')))
		return (destroy((void**)&list));
	list->env = env;
	list->next = NULL;
	return (list);
}

int			varlist_push_raw(t_varlist ** list_ptr, const char * raw_data, int env)
{
	t_varlist * new_var;

	if (!(new_var = varlist_new_raw(raw_data, env)))
		return (-1);
	if (*list_ptr)
		varlist_last(*list_ptr)->next = new_var;
	else
		*list_ptr = new_var;
	return (0);
}

void		varlist_sort(t_varlist * list, int (*cmpf)(const char *, const char *))
{
	t_varlist * head;

	while (list)
	{
		head = list->next;
		while (head)
		{
			if ((*cmpf)(list->var, head->var) > 0)
			{
				swap_ptr((void**)&list->var, (void**)&head->var);
				swap_int(&list->env, &head->env);
			}
			head = head->next;
		}
		list = list->next;
	}
}

void *		varlist_clear(t_varlist ** list_ptr)
{
	t_varlist * head;

	while (*list_ptr)
	{
		head = (*list_ptr)->next;
		destroy((void**)list_ptr);
		*list_ptr = head;
	}
	return (NULL);
}

size_t		varlist_size(const t_varlist * list)
{
	size_t	size;

	size = 0;
	while (list)
	{
		size++;
		list = list->next;
	}
	return (size);
}
