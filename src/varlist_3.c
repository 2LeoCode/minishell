/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varlist_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 00:49:54 by lsuardi           #+#    #+#             */
/*   Updated: 2021/03/04 20:42:53 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <varlist.h>

static void *	varlist_get_array_failure(char *** data)
{
	char ** it = (*data - 1);

	while (*(++it))
		destroy((void**)it);
	free(*data);
	*data = NULL;
	return (NULL);
}

static size_t	varlist_get_env_count(const t_varlist * list)
{
	size_t		count;

	count = 0;

	while (list)
	{
		count += !!list->env;
		list = list->next;
	}
	return (count);
}

static size_t	varlist_get_nonenv_count(const t_varlist * list)
{
	size_t		count;

	count = 0;

	while (list)
	{
		count += !list->env;
		list = list->next;
	}
	return (count);
}

char **			varlist_get_env_array(const t_varlist * list)
{
	char **	env;
	char ** it;
	size_t	size;

	size = varlist_get_env_count(list);
	if (!(env = (char**)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	env[size] = NULL;
	it = env;
	while (list)
	{
		if (list->env && !(*(it++) = ft_strdup(list->var)))
			return (varlist_get_array_failure(&env));
		list = list->next;
	}
	return (env);
}

char **			varlist_get_nonenv_array(const t_varlist * list)
{
	char **	env;
	char ** it;
	size_t	size;

	size = varlist_get_nonenv_count(list);
	if (!(env = (char**)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	env[size] = NULL;
	it = env;
	while (list)
	{
		if (!list->env && !(*(it++) = ft_strdup(list->var)))
			return (varlist_get_array_failure(&env));
		list = list->next;
	}
	return (env);
}
