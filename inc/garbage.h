/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 01:11:16 by lsuardi           #+#    #+#             */
/*   Updated: 2021/04/09 01:21:58 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_H
# define GARBAGE_H

# include <list.h>

typedef void	(*t_destructor)(void *);

typedef struct	s_pair
{
	void	*first;
	void	*second;
}	t_pair;

int	garbage_collector(void *data, t_destructor destructor, int action);
int	gb_alloc(void **data, size_t size);
int	gb_add(void *data, t_destructor destructor);
int	gb_save(void);
int	gb_load(void);
int	gb_clear(void);

#endif
