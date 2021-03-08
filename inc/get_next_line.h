/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 15:35:48 by lsuardi           #+#    #+#             */
/*   Updated: 2021/03/04 01:23:51 by lsuardi          ###   ########.fr       */
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

typedef struct		s_list
{
	char			buf[BUFFER_SIZE + 1];
	char			*pos;
	struct s_list	*next;
}					t_list;

typedef struct		s_buffer
{
	int				read_ret;
	int				init;
	int				id;
	t_list			*all;
	t_list			*last;
	t_list			*cur;
}					t_buffer;

int					get_next_line(int fd, char **line);
void				*lst_chr(t_list *lst, int c);
int					clear_buffer(t_buffer *buf);
#endif
