/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervision.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 09:33:40 by maustel           #+#    #+#             */
/*   Updated: 2024/09/26 12:45:52 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// past - args->philos[i].last_meal_time > args->time_to_die
// 				&& !args->philos[i].full

static bool	philo_died(t_philo philo)
{
	long	past_time;
	long	last_meal_time;

	past_time = gettime_us(philo.args) - philo.args->start_simulation;
	last_meal_time = get_long(philo.args,
		philo.philo_mutex, philo.last_meal_time);
	if (past_time - last_meal_time > philo.args->time_to_die)
		return (true);
	else
		return (false);
}

/*
	check if all threads are running (nbr_philos_ready)
*/
bool	all_philos_active(t_arguments *args)
{
	bool	ret;

	ret = false;
	safe_mutex(args, &args->args_mutex, LOCK);
	if (args->nbr_philos == args->nbr_philos_ready)
		ret = true;
	else
		ret = false;
	safe_mutex(args, &args->args_mutex, UNLOCK);
	return (ret);
}

/*
	wait for all threads running
	if the past time is bigger than time_to_die and philo is not full
		->simulation ends
*/
void	*supervise_meal(void *ar)
{
	t_arguments	*args;
	int			i;
	long		past;

	args = (t_arguments *) ar;
	while (!all_philos_active(args))
		usleep(100);
	while (!simulation_finished(args))
	{
		i = 0;
		while (i < args->nbr_philos && !simulation_finished(args))
		{
			past = gettime_us(args) - args->start_simulation;
			if (!get_bool(args, args->philos[i].philo_mutex, args->philos[i].full)
				&& philo_died(args->philos[i]))
				{
					set_bool(args, args->args_mutex, &args->end_simulation, true);
					print_status(args, args->philos[i], DIED);
				}
			i++;
		}
	}
	return (NULL);
}
