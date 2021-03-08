/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varlist_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 23:35:48 by lsuardi           #+#    #+#             */
/*   Updated: 2021/03/04 22:12:52 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <varlist.h>

int	varlist_rm(t_varlist ** list_ptr, const t_varlist * target)
{
	t_varlist * head;
	t_varlist * cur;
	t_varlist * prev;

	cur = *list_ptr;
	while (cur)
	{
		head = cur->next;
		if (cur == target)
		{
			destroy((void**)&cur->env);
			destroy((void**)&cur);
			if (prev)
				prev->next = head;
			else
				*list_ptr = head;
			return (1);
		}
		prev = cur;
		cur = cur->next;
	}
	return (0);
}

int varlist_cmp_name(const char * var, const char * name)
{
	return (ft_strncmp(env, name, ft_strlen(name)));
}

int	varlist_cmp_data(const char * var, const char * data)
{
	while (*env && (*(env++) != '='))
		continue ;
	if (!env)
	{
		write(2, "minishell: Internal error (varlist_cmp_data)\n", 45);
		return (-1);
	}
	return (ft_strcmp(env, data));
}

int	varlist_rm_if(t_varlist ** list_ptr, const char * data_ref, int (*cmpf)(const char *, const char *))
{
	t_varlist * list;

	list = *list_ptr;
	while (list)
	{
		if (!(cmpf)(list->env, data_ref))
			return (varlist_rm(list_ptr, list));
		list = list->next;
	}
	return (0);
}

int varlist_copy(t_varlist ** dst, const t_varlist * src, const char * var)
{
	size_t		len;

	len = ft_strlen(var);
	while (src && ft_strncmp(src->var, var, len))
		src = src->next;
	if (!src)
		return (1);
	if (varlist_push_raw(dst, src->var, src->env))
		return (-1);
	return (0);
}
