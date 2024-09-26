/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:12:08 by maustel           #+#    #+#             */
/*   Updated: 2024/09/26 17:41:43 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	simulation_finished(t_arguments *args)
{
	bool	finished;

	finished = false;
	finished = get_bool(args, &args->end_mutex, &args->end_simulation);
	return (finished);
}

void	set_bool(t_arguments *args, t_mtx *mutex, bool *dest, bool value)
{
	safe_mutex(args, mutex, LOCK);
	*dest = value;
	safe_mutex(args, mutex, UNLOCK);
}

bool	get_bool(t_arguments *args, t_mtx *mutex, bool *dest)
{
	bool	ret;

	safe_mutex(args, mutex, LOCK);
	ret = *dest;
	safe_mutex(args, mutex, UNLOCK);
	return (ret);
}

void	set_long(t_arguments *args, t_mtx *mutex, long *dest, long value)
{
	safe_mutex(args, mutex, LOCK);
	*dest = value;
	safe_mutex(args, mutex, UNLOCK);
}

long	get_long(t_arguments *args, t_mtx *mutex, long *dest)
{
	long	ret;

	ret = 0;
	safe_mutex(args, mutex, LOCK);
	ret = *dest;
	safe_mutex(args, mutex, UNLOCK);
	return (ret);
}

void	increment(t_arguments *args, t_mtx *mutex, long *dest)
{
	safe_mutex(args, mutex, LOCK);
	*dest = *dest + 1;
	safe_mutex(args, mutex, UNLOCK);
}
