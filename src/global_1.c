/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 22:28:33 by lsuardi           #+#    #+#             */
/*   Updated: 2021/03/08 18:41:37 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char *	update_global_env(const t_varlist * local)
{
	char **		new_env;
	char **		it;
	size_t		size;
	t_varlist *	tmp;

	tmp = local;
	while (tmp)
	{
		if (tmp->env)
			size++;
		tmp = tmp->next;
	}
	if (!(new_env = (char**)malloc(sizeof(char*) * (size + 1))))
		return (destroy_global(ENV));
	new_env[size] = NULL;
	it = new_env;
	while (local)
	{
		if (local->env && !(*(it++) = ft_strdup(local->var)))
			return (destroy_global(ENV));
		local = local->next;
	}
	destroy_global(ENV);
	g_env = new_env;
	return (g_env);
}

char *	update_global_var(const t_varlist * local)
{
	char **		new_var;
	char **		it;
	size_t		size;
	t_varlist *	tmp;

	tmp = local;
	while (tmp)
	{
		if (!tmp->env)
			size++;
		tmp = tmp->next;
	}
	if (!(new_env = (char**)malloc(sizeof(char*) * (size + 1))))
		return (destroy_global(NENV));
	new_env[size] = NULL;
	it = new_var;
	while (local)
	{
		if (!local->env && !(*(it++) = ft_strdup(local->var)))
			return (destroy_global(NENV));
		local = local->next;
	}
	destroy_global(NENV);
	g_var = new_var;
	return (g_env);
}
