/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:12:08 by maustel           #+#    #+#             */
/*   Updated: 2024/09/27 17:02:44 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	simulation_finished(t_arguments *args)
{
	return (get_bool(&args->end_mutex, &args->end_simulation));
}

void	set_bool(t_mtx *mutex, bool *dest, bool value)
{
	safe_mutex(mutex, LOCK); //return(err(E_MUTEX))
	*dest = value;
	safe_mutex(mutex, UNLOCK);
}

bool	get_bool(t_mtx *mutex, bool *dest)
{
	bool	ret;

	safe_mutex(mutex, LOCK); //return(err(E_MUTEX))
	ret = *dest;
	safe_mutex(mutex, UNLOCK);//return(err(E_MUTEX))
	return (ret);
}

void	set_long(t_mtx *mutex, long *dest, long value)
{
	safe_mutex(mutex, LOCK); //return(err(E_MUTEX))
	*dest = value;
	safe_mutex(mutex, UNLOCK); //return(err(E_MUTEX))
}

long	get_long(t_mtx *mutex, long *dest)
{
	long	ret;

	ret = 0;
	safe_mutex(mutex, LOCK); //return(err(E_MUTEX))
	ret = *dest;
	safe_mutex(mutex, UNLOCK); //return(err(E_MUTEX))
	return (ret);
}

void	increment(t_mtx *mutex, long *dest)
{
	safe_mutex(mutex, LOCK); //return(err(E_MUTEX))
	*dest += 1;
	safe_mutex(mutex, UNLOCK);
}
