/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varlist_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 22:08:37 by lsuardi           #+#    #+#             */
/*   Updated: 2021/03/07 19:33:25 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <varlist.h>

int		varlist_export(t_varlist ** var, const char * name)
{
	t_varlist *	list;
	size_t		len;

	list = *var;
	len = ft_strlen(name);
	while (list)
	{
		if (!varlist_cmp_name(list->var, name))
		{
			list->env = 1;
			return (0);
		}
		list = list->next;
	}
	return (1);
}

int		varlist_set_raw(t_varlist ** var, const char * raw_data, int env)
{
	char *	tmp;
	int		ret;

	if (!(tmp = ft_strdup(raw_data)))
		return (-1);
	str_replace_chr(tmp, '=', 0);
	ret = varlist_set(var, tmp, tmp + ft_strlen(tmp) + 1, env);
	destroy((void**)&tmp);
	return (ret);
}
