/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:21:47 by maustel           #+#    #+#             */
/*   Updated: 2024/09/13 14:36:26 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_arguments *args, t_philo philo, t_philo_status status)
{
	long	time;

	time = gettime_us(args) - args->start_simulation;
	safe_mutex(args, &args->write_mutex, LOCK);
	if (status == FORK)
		printf("%l   %d has taken a fork", time, philo.id);
	else if (status == EAT)
		printf("%l   %d is eating", time, philo.id);
	else if (status == SLEEP)
		printf("%l   %d is sleeping", time, philo.id);
	else if (status == THINK)
		printf("%l   %d is thinking", time, philo.id);
	else if (status == DIED)
		printf("%l   %d died", time, philo.id);
	else
		error_exit(args, "wrong philo_status code");
	safe_mutex(args, &args->write_mutex, UNLOCK);
}
