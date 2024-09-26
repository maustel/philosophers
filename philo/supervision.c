/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervision.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 09:33:40 by maustel           #+#    #+#             */
/*   Updated: 2024/09/26 16:52:04 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	philo_died(t_philo philo)
{
	long	past_time;
	long	last_meal_time;
	long	start_sim;

	start_sim= get_long(philo.args, philo.args->start_mutex, philo.args->start_simulation);

	past_time = gettime_us(philo.args) - start_sim;
	last_meal_time = get_long(philo.args,
		philo.meal_time_mutex, philo.last_meal_time);
	// printf("now:%ld\n", gettime_us(philo.args));
	// printf("start_sim:%ld\n", philo.args->start_simulation);
	// printf("start_sim:%ld\n", get_long(philo.args, philo.args->start_mutex, philo.args->start_simulation));
	// printf("past time: %ld\nlast meal: %ld\ntime to die: %d\nstart_sim:%ld\n", past_time, last_meal_time, philo.args->time_to_die, start_sim);
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
	long	nbr_ready;

	nbr_ready = get_long(args, args->nbr_ready_mutex, args->nbr_philos_ready);
	if (nbr_ready == args->nbr_philos)
		return (true);
	else
		return (false);
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

	args = (t_arguments *) ar;
	printf("[[philos ready: %d]]\n", get_bool(args, args->all_ready_mutex, args->all_philos_ready));
	while (!get_bool(args, args->all_ready_mutex, args->all_philos_ready))
		usleep(10);
	// while (!all_philos_active(args))
	// 	usleep(10);
	printf("SUPERVISOR ACTIVE\n");
	while (!simulation_finished(args))
	{
		i = 0;
		while (i < args->nbr_philos && !simulation_finished(args))
		{
			if (!get_bool(args, args->philos[i].full_mutex, args->philos[i].full)
				&& philo_died(args->philos[i]))
				{
					set_bool(args, args->end_mutex, &args->end_simulation, true);
					print_status(args, args->philos[i], DIED);
					break ;
				}
			i++;
		}
	}
	return (NULL);
}
