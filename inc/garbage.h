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

int		garbage_collector(void *data, t_destructor destructor, int action);
int		garbage_add(void *data, t_destructor destructor);
void	garbage_save(void);
void	garbage_load(void);
void	garbage_clear(void);

#endif
