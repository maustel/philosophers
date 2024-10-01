/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:10:20 by maustel           #+#    #+#             */
/*   Updated: 2024/10/01 10:10:25 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	returns time in microseconds
*/
long	gettime_us(void)
{
	struct timeval time_value;

	if (gettimeofday(&time_value, NULL))
		return (err(E_GETTIME));
		// error_exit(args, "Error gettimeofday");
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
			break;
		usleep(250);
	}
}

// /*
// 	original usleep is not precise enough.
// 	-> Gives us at least the time we ask, but often more.
// 	This function: When remaining time = (now - start) is still far away
// 	(> 1 ms) from time_to_sleep (sleeptime) -> usleep (rem/2).
// 	If it is very close, usleep(0.1), so we wont miss the exact sleeptime
// */
// void	exact_usleep(long sleeptime_us, t_arguments *args)
// {
// 	long	start;
// 	long	past;
// 	long	rem;

// 	start = gettime_us(args);
// 	while (gettime_us(args) - start < sleeptime_us)
// 	{
// 		if (simulation_finished(args))
// 			break ;
// 		past = gettime_us(args) - start;
// 		rem = sleeptime_us - past;
// 		if (rem > 1000)
// 			usleep(rem / 2);
// 		else
// 		{
// 			while (gettime_us(args) - start < sleeptime_us)
// 				usleep(1);
// 		}
// 	}
// }


