/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 23:54:54 by lsuardi           #+#    #+#             */
/*   Updated: 2021/03/28 23:55:05 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int     is_valid_nflag(char *str)
{
    int i;

    i = 1;
    while (str[i] && str[i] == 'n')
        i++;
    if (str[i] == ' ' || str[i] == '\0')
        return (1);
    return (0);
}

void    ft_putecho(char **av, int ac, bool *n_flag)
{
    int i;

    i = 1;
    while (i < ac) 
    {   
        if (ft_strcmp(av[i], "-n") == 0 || (i == 1 && ft_strncmp(av[i], "-n", 2) == 0
        && is_valid_nflag(av[i])))
        {   
                *n_flag = true;
                av++;
                ac--;
        }   
        else
        {   
            if (i != 1 && ft_strcmp(av[i - 1], "-n") != 0)
                ft_putchar_fd(' ', 1); 
            ft_putstr(av[i]);
            i++;
        }   
    }  
    if (!*n_flag)
        ft_putchar_fd('\n', 1); 
}

int builtin_echo(int ac, char **av, char **ep)
{
	(void)ep, (void)ac, (void)av;
	return (0);
	bool n_flag;

	(void)ep;
	if (ac == 1)
	{   
		ft_putchar_fd('\n', 1); 
		return (0);
	}
	n_flag = false;
	ft_putecho(av, ac, &n_flag);
	return (0);
}
