/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:10:20 by maustel           #+#    #+#             */
/*   Updated: 2024/09/12 18:11:54 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	simulation_finished(t_arguments *args)
{
	bool	finished;

	finished = false;
	pthread_mutex_lock(&args->args_mutex);
	if (args->end_simulation == true)
		finished = true;
	else
		finished = false;
	pthread_mutex_unlock(&args->args_mutex);
	return (finished);
}

/*
	time_code = SECONDS MILLISECONDS MICROSECONDS
*/
long	gettime(t_arguments *args, t_time_code time_code)
{
	struct timeval time_value;
	if (gettimeofday(&time_value, NULL))
		error_exit(args, "Error gettimeofday");
	if (time_code == SECOND)
		return (time_value.tv_sec + (time_value.tv_usec / 1e6));
	else if (time_code == MILLISECOND)
		return ((time_value.tv_sec * 1e3) + (time_value.tv_usec) /1e3);
	else if (time_code == MICROSECOND)
		return ((time_value.tv_sec * 1e6) + time_value.tv_usec);
	else
		error_exit(args, "Wrong input gettime()");
	return (42);
}

/*
	original usleep is not precise enough
*/
void	precise_usleep(long usec, t_arguments *args)
{
	long	start;
	long	past;
	long	rem;

	start = gettime(args, MICROSECOND);
	while (gettime(args, MICROSECOND) - start < usec)
	{
		if (simulation_finished(args))
			break ;
		past = gettime(args, MICROSECOND) - start;
		rem = usec - past;
		if (rem > 1e3)
			usleep(usec / rem);
		else
		{
			while (gettime(args, MICROSECOND) - start < usec)
				;
		}
	}

}
