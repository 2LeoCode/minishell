/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 23:10:44 by lsuardi           #+#    #+#             */
/*   Updated: 2021/03/07 19:28:39 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void *		destroy(void ** mem)
{
	if (*mem)
	{
		free(*mem);
		*mem = NULL;
	}
	return (NULL);
}

void		swap_int(int * a, int * b)
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void		swap_ptr(void ** a, void ** b)
{
	void * tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int			ft_isspace(char c)
{
	return (!!ft_strchr(" \n\b\r\v\f\t", c));
}

long long	ft_atoll(const char * s)
{
	long long	n;
	long long	sign;

	n = 0;
	sign = 1;
	while (ft_isspace(*s))
		s++;
	if ((*s == '+') || (*s == '-'))
		sign -= 2 * (*(s++) == '-');
	while ((*s >= '0') && (*s <= '9'))
		n = 10 * n + (*(s++) - '0');
	return (sign * n);
}
