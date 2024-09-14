/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervision.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 09:33:40 by maustel           #+#    #+#             */
/*   Updated: 2024/09/14 14:52:21 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		usleep(10);
	while (!simulation_finished(args))
	{
		i = 0;
		while (i < args->nbr_philos && !simulation_finished(args))
		{
			past = gettime_us(args) - args->start_simulation;
			if (past - args->philos[i].last_meal_time > args->time_to_die
				&& !args->philos[i].full)
				{
					set_bool(args, args->args_mutex, &args->end_simulation, true);
					print_status(args, args->philos[i], DIED);
				}
			i++;
		}
	}
	return (NULL);
}
