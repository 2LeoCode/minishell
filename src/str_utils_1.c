/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 20:22:23 by lsuardi           #+#    #+#             */
/*   Updated: 2021/03/07 20:46:14 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char *			ft_strncat(char * dst, const char * src, size_t n)
{
	char * begin;

	begin = dst;
	while (*dst)
		dst++;
	ft_strncpy(dst, src, n);
	return (begin);
}

char *			ft_strjoin(const char * s1, const char * s2, char sep)
{
	char *	join;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (!(join = (char*)malloc(sizeof(char) * (s1_len + s2_len + 1 + !!sep))))
		return (NULL);
	join[s1_len] = sep;
	join[s1_len + !!sep] = 0;
	ft_strncpy(join, s1, s1_len);
	return (ft_strncat(join, s2, s2_len + 1));
}

char *			str_replace_chr(char * s, int before, int after)
{
	char * it;

	it = s - 1;
	while (*(++it))
		if (*it == (char)before)
			*it = (char)after;
	return (s);
}

char *			str_replace(char ** s, const char * before, const char * after)
{
	char *	it;
	char *	new;
	int		len_before;
	int		len_after;
	int		size;

	len_before = (int)ft_strlen(before);
	len_after = (int)ft_strlen(after);
	size = (int)ft_strlen(*s) + (len_after - len_before)
	* number_of_occurences(*s, before);
	if (!(new = (char*)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	new[size] = 0;
	size = 0;
	it = *s - 1;
	while (*(++it))
		if ((*it == *before) && !ft_strncmp(it, before, len_before))
		{
			it += len_before - 1;
			ft_strcpy(new + size, after);
			size += len_after;
		}
		else
			new[size++] = *it;
	return (new);
}

char *			ft_strchr(const char * s, int c)
{
	while (*s && (*s != c))
		s++;
	return (*s ? s : NULL);
}
