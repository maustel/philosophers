/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 10:26:10 by maustel           #+#    #+#             */
/*   Updated: 2024/10/01 10:29:16 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*one_philo(void *ph)
{
	t_philo *philo;

	philo = (t_philo *) ph;

	while (!get_bool(&philo->args->all_ready_mutex,
			&philo->args->all_philos_ready))
		usleep(10);
	increment(&philo->args->nbr_ready_mutex,
		&philo->args->nbr_philos_ready);
	set_long(&philo->args->start_mutex,
		&philo->args->start_simulation, gettime_us());
	if (print_status(philo->args, *philo, FORK))
		return (NULL);
	while (!simulation_finished(philo->args))
		usleep(100);
	return (NULL);
}

/*
	if nbr philos is even -> system is already fair
	if nbr is odd, there can be unfair scenarios (like one philo
	eats towo times in a row)
	-> force philos to think for at least a certain time
	time_to_think is the available time to think
*/
void	think(t_arguments *args, t_philo *philo)
{
	int	time_to_think;

	if (simulation_finished(args))
		return ;
	print_status(args, *philo, THINK);
	if (philo->args->nbr_philos % 2 == 0)
		return ;
	time_to_think = args->time_to_eat * 2 - args->time_to_sleep;
	if (time_to_think < 0)
		return;
	exact_usleep(time_to_think * 0.5, args);
}

void	sleeping(t_arguments *args, t_philo philo)
{
	if (simulation_finished(args))
		return ;
	print_status(args, philo, SLEEP);
	exact_usleep(args->time_to_sleep, args);
}

/*
	takes both forks and print status
	when he has both forks, starts to eat, print status
	update last_meal_time
	update meals_count
	if philo is full, update full=true
	usleep(time_to_eat)
	release forks
*/
int	eat(t_arguments *args, t_philo *philo)
{
	long	start_sim;

	if (safe_mutex(&philo->first_fork->fork_mutex, LOCK))
		return(err(E_MUTEX));
	print_status(args, *philo, FORK);
	if (safe_mutex(&philo->second_fork->fork_mutex, LOCK))
		return(err(E_MUTEX));
	print_status(args, *philo, FORK);
	start_sim = get_long(&args->start_mutex, &args->start_simulation);
	set_long(&philo->meal_time_mutex, &philo->last_meal_time,
			gettime_us() - start_sim);
	print_status(args, *philo, EAT);
	// increment(&philo->count_mutex, &philo->meals_count);
	// if (philo_full(args, *philo))
	// 	set_bool(&philo->full_mutex, &philo->full, true);
	exact_usleep(args->time_to_eat, args);
	if (safe_mutex(&philo->first_fork->fork_mutex, UNLOCK))
		return(err(E_MUTEX));
	if (safe_mutex(&philo->second_fork->fork_mutex, UNLOCK))
		return(err(E_MUTEX));
	philo->meals_count++;
	if (args->nbr_must_eat > 0 && philo->meals_count == args->nbr_must_eat)
		set_bool(&philo->full_mutex, &philo->full, true);
	return (0);
}