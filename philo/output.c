/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:21:47 by maustel           #+#    #+#             */
/*   Updated: 2024/09/26 17:43:23 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_arguments *args, t_philo philo, t_philo_status status)
{
	long	time_ms;
	long	start_sim;

	start_sim = get_long(args, &args->start_mutex, &args->start_simulation);
	time_ms = (gettime_us(args) - start_sim) / 1e3;
	safe_mutex(args, &args->output_mutex, LOCK);
	if (!simulation_finished(args))
	{
		if (status == FORK)
			printf("%ld   %d has taken a fork\n", time_ms, philo.id);
		else if (status == EAT)
		{
			printf("%ld   %d is eating\n", time_ms, philo.id);
			// printf("[[Philo %d just had Meal nbr: %ld]]\n", philo.id, philo.meals_count + 1);
			///remove decond printf
		}
		else if (status == SLEEP)
			printf("%ld   %d is sleeping\n", time_ms, philo.id);
		else if (status == THINK)
			printf("%ld   %d is thinking\n", time_ms, philo.id);
	}
	else if (status == DIED)
		printf("\033[31;1m%ld   %d died\033[0m\n", time_ms, philo.id);
	safe_mutex(args, &args->output_mutex, UNLOCK);
}
