/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 23:55:40 by lsuardi           #+#    #+#             */
/*   Updated: 2021/03/28 23:55:44 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_printexp(char **ep)
{
	char	*rpl;

	while (*ep)
	{
		if (ft_strncmp(*ep, "_=", 2))
		{
			ft_putstr("declare -x ");
			rpl = ft_rplchr(*ep, '=', 0);
			ft_putstr(*ep);
			if (rpl)
			{
				ft_putstr("=\"");
				ft_putstr(rpl + 1);
				ft_putendl("\"");
			}
		}
		ep++;
	}
}

int	is_valid_arg(char *str)
{
	int	len;
	int	i;

	len = ft_strlen(str);
	i = 0;
	if (!(ft_isalpha(str[i]) || str[i] == '_'))
		return (0);
	while (++i < len && str[i] != '=')
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (0);
	}
	return (1);
}

int	update_path(const char *new_path, bool update_env)
{
	char	**new_split;

	if (update_env && ft_setenv("PATH", new_path))
		return (-1);
	if (new_path)
	{
		new_split = ft_split(new_path, ':');
		if (!new_split)
			return (-1);
	}
	else
		new_split = NULL;
	ft_destroy_array((void **)g_global_data.path, NULL_ENDED);
	g_global_data.path = new_split;
	return (0);
}

int	builtin_export(int argc, char **argv, char **envp)
{
	char	*rpl;
	int		ret;

	while (*argv)
	{
		if (!is_valid_arg(*argv))
			return (1);
		rpl = ft_rplchr(*argv, '=', '\0');
		if (!ft_strcmp(*argv, "PATH"))
		{
			rpl += !!rpl;
			ret = update_path(rpl, true);
		}
		else if (!rpl && !ft_getenv(*argv))
			ret = ft_setenv(*argv, NULL);
		else
			ret = ft_setenv(*argv, rpl + 1);
		if (ret == -1)
			return (-1);
		argv++;
	}
	if (argc == 1)
		ft_printexp(envp);
	return (0);
}
