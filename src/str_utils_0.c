/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils_0.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 00:44:21 by lsuardi           #+#    #+#             */
/*   Updated: 2021/03/01 21:16:47 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

size_t	ft_strlen(const char * s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

int		ft_strcmp(const char * s1, const char * s2)
{
	while ((*s1 || *s2) && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

int		ft_strncmp(const char * s1, const char * s2, size_t n)
{
	while (n-- && (*s1 || *s2) && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((n != ULONG_MAX) * ((unsigned char)*s1 - (unsigned char)*s2));
}

char *	ft_strncpy(char * dst, const char * src, size_t n)
{
	char *	begin;

	begin = dst;
	while (n--)
		*(dst++) = (*src ? *(src++) : 0);
	return (begin);
}

char *	ft_strdup(const char * s)
{
	char *	new_s;
	size_t	len;

	len = ft_strlen(new_s);
	if (!(new_s = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	return (ft_strncpy(new_s, s, len + 1));
}
