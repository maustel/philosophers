/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:12:08 by maustel           #+#    #+#             */
/*   Updated: 2024/10/01 10:24:51 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_bool(t_mtx *mutex, bool *dest, bool value)
{
	safe_mutex(mutex, LOCK);
	*dest = value;
	safe_mutex(mutex, UNLOCK);
}

bool	get_bool(t_mtx *mutex, bool *dest)
{
	bool	ret;

	safe_mutex(mutex, LOCK);
	ret = *dest;
	safe_mutex(mutex, UNLOCK);
	return (ret);
}

void	set_long(t_mtx *mutex, long *dest, long value)
{
	safe_mutex(mutex, LOCK);
	*dest = value;
	safe_mutex(mutex, UNLOCK);
}

long	get_long(t_mtx *mutex, long *dest)
{
	long	ret;

	ret = 0;
	safe_mutex(mutex, LOCK);
	ret = *dest;
	safe_mutex(mutex, UNLOCK);
	return (ret);
}

void	increment(t_mtx *mutex, long *dest)
{
	safe_mutex(mutex, LOCK);
	*dest += 1;
	safe_mutex(mutex, UNLOCK);
}
