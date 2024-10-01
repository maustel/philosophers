/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:10:20 by maustel           #+#    #+#             */
/*   Updated: 2024/10/01 16:01:51 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	simulation_finished(t_arguments *args)
{
	return (get_bool(&args->end_mutex, &args->end_simulation));
}

/*
	returns time in microseconds
*/
long	gettime_us(void)
{
	struct timeval	time_value;

	if (gettimeofday(&time_value, NULL))
		return (err(E_GETTIME));
	else
		return ((long)(time_value.tv_sec * 1e6 + time_value.tv_usec));
	return (42);
}

/*
	original usleep is not good enough,
	because i need to check if simulation has stopped in the meatime
*/
void	exact_usleep(long sleeptime_us, t_arguments *args)
{
	long	start;

	start = gettime_us();
	while (gettime_us() - start < sleeptime_us)
	{
		if (simulation_finished(args))
			break ;
		usleep(250);
	}
}

bool	safe_mutex(t_mtx *mutex, t_safe_mutex todo)
{
	if (todo == INIT)
		return (pthread_mutex_init(mutex, NULL));
	else if (todo == LOCK)
		return (pthread_mutex_lock(mutex));
	else if (todo == UNLOCK)
		return (pthread_mutex_unlock(mutex));
	else if (todo == DESTROY)
		return (pthread_mutex_destroy(mutex));
	else
		return (1);
	return (0);
}
