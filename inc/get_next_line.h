/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 15:35:48 by lsuardi           #+#    #+#             */
/*   Updated: 2021/04/06 21:10:54 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif
# define MAX_FD 9999

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>

/*
**	Structure containing the read buffer, and two ints: `cursor` which
**	corresponds to our current position inside the buffer, and `len` which is
**	the length of the string inside the buffer (it means that if
**	`len` < BUFFER_SIZE, we reached the end of the file)
*/
typedef struct s_buffer
{
	int			cursor;
	int			len;
	char		rd_buf[BUFFER_SIZE + 1];
}	t_buffer;

/*
**	Utilities
*/
size_t	_ft_strlen(const char *s);
char	*_ft_strdup(const char *s);
bool	_ft_str_replace_first(char *s, int before, int after);
char	*_ft_strjoin(const char *prefix, const char *suffix);

/*
**	Main function
*/
int		get_next_line(int fd, char **line);

#endif
