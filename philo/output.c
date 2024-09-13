/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:21:47 by maustel           #+#    #+#             */
/*   Updated: 2024/09/13 16:39:18 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_arguments *args, t_philo philo, t_philo_status status)
{
	long	time_ms;

	time_ms = (gettime_us(args) - args->start_simulation) / 1e3;
	safe_mutex(args, &args->write_mutex, LOCK);
	if (status == FORK)
		printf("%ld   %d has taken a fork\n", time_ms, philo.id);
	else if (status == EAT)
		printf("%ld   %d is eating\n", time_ms, philo.id);
	else if (status == SLEEP)
		printf("%ld   %d is sleeping\n", time_ms, philo.id);
	else if (status == THINK)
		printf("%ld   %d is thinking\n", time_ms, philo.id);
	else if (status == DIED)
		printf("%ld   %d died\n", time_ms, philo.id);
	else
		error_exit(args, "wrong philo_status code");
	safe_mutex(args, &args->write_mutex, UNLOCK);
}
