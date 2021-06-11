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

/*void	ft_printexp(char **ep)
{
	while (*ep)
	{
		if (ft_strncmp(*ep, "_=", 2))
			printf("%s\n", *ep);			
		ep++;
	}
}

int		is_valid_arg(char *str)
{
	int	len;
	int i;

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

int		export_failure(int error)
{
	printf("syntax error");
	return (error);
}*/

int		builtin_export(int ac, char ** av, char ** ep)
{
	(void)ep, (void)ac, (void)av;
	return (0);
	/*char	*rpl;
	int		ret;

	while (*av)
	{
		if (!is_valid_arg(*av))
			return (export_failure(1));
		rpl = ft_rplchr(*av, '=', '\0');
		if (!rpl)
			ret = ft_setenv(*av, NULL);
		else
			ret = ft_setenv(*av, rpl + 1);
		if (ret == -1)
			return (export_failure(-1));
		av++;
	}
	if (ac == 1)
		ft_printexp(ep);
	return (0);*/
}
