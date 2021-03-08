/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 20:41:42 by lsuardi           #+#    #+#             */
/*   Updated: 2021/03/07 20:44:21 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

size_t	number_of_occurences(const char * haystack, const char * needle)
{
	size_t	count;
	size_t	needle_len;

	count = 0;
	needle_len = ft_strlen(needle);
	while (*haystack)
		if ((*haystack == needle) && !ft_strncmp(haystack, needle, needle_len))
		{
			count++;
			haystack += needle_len;
		}
		else
			haystack++;
	return (count);
}
