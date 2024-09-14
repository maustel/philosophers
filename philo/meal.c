/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meal.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:40:39 by maustel           #+#    #+#             */
/*   Updated: 2024/09/14 13:19:14 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	0) if meals==0 -> return (0)]
	0.1) if nbr_philo == 1 -> ??
	1) create all threads (philos)
	2) create an observing monitor thread, that looks for died philos
	3) synchroonize beginning of simulation
		->every philo starts simultaneously
	4) Join everyone
*/

void	*one_philo(void *ph)
{
	t_philo *philo;

	philo = (t_philo *) ph;

	while (!get_bool(philo->args, philo->args->args_mutex,
			philo->args->all_philos_ready))
		usleep(10);
	set_long(philo->args, philo->args->args_mutex,
		&philo->args->nbr_philos_ready, philo->args->nbr_philos_ready + 1);
	set_long(philo->args, philo->args->args_mutex,
		&philo->args->start_simulation, gettime_us(philo->args));
	print_status(philo->args, *philo, FORK);
	while (!simulation_finished(philo->args))
		usleep(100);
	return (NULL);
}

static void	think(t_arguments *args, t_philo philo)
{
	print_status(args, philo, THINK);
}

static void	sleeping(t_arguments *args, t_philo philo)
{
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
static void	eat(t_arguments *args, t_philo *philo)
{
	safe_mutex(args, &philo->first_fork->fork, LOCK);
	print_status(args, *philo, FORK);
	safe_mutex(args, &philo->second_fork->fork, LOCK);
	print_status(args, *philo, FORK);
	print_status(args, *philo, EAT);
	set_long(args, philo->philo_mutex, &philo->last_meal_time,
			gettime_us(args) - (long)args->start_simulation);
	set_long(args, philo->philo_mutex, &philo->meals_count,
			philo->meals_count + 1);
	if (args->nbr_must_eat > 0 && args->nbr_must_eat == philo->meals_count)
		set_bool(args, philo->philo_mutex, &philo->full, true);
	exact_usleep(args->time_to_eat, args);
	safe_mutex(args, &philo->first_fork->fork, UNLOCK);
	safe_mutex(args, &philo->second_fork->fork, UNLOCK);
}

/*
	synchronize beginning of simulation
	-> wait for all philos
	->every philo starts simultaneously
	wait for all threads -> waitingloop
	check if args->all_philos_ready - flag is already set to true
	(is set in meal_start)
	Then increase the number of philos_ready
*/
void	*meal_simulation(void *ph)
{
	t_philo *philo;

	philo = (t_philo *) ph;
	while (!get_bool(philo->args, philo->args->args_mutex,
			philo->args->all_philos_ready))
		usleep(10);
	set_long(philo->args, philo->args->args_mutex,
		&philo->args->nbr_philos_ready, philo->args->nbr_philos_ready + 1);
	while (!simulation_finished(philo->args) && !philo->full)
	{
		eat(philo->args, philo);
		// philo full? -> break?
		sleeping(philo->args, *philo);
		think(philo->args, *philo);
	}
	return (NULL);
}


/*
	each philo remains in waitingloop until all of them are created
*/
void	create_philo_threads(t_arguments *args)
{
	int	i;

	i = 0;
	while (i < args->nbr_philos)
	{
		if (pthread_create(&args->philos[i].thread_id, NULL,
			meal_simulation, &args->philos[i]))
				error_exit(args, "pthread create failed");
		i++;
		printf("thread\n");
	}
}

/*
	create one thread for each philo
	only if all threads are made and ready we start simulation
*/
void	meal_start(t_arguments *args)
{
	int	i;

	i = 0;
	if (args->nbr_philos == 1)
	{
		if (pthread_create(&args->philos[0].thread_id, NULL,
			one_philo, &args->philos[i]))
				error_exit(args, "pthread create failes");
	}
	else
		create_philo_threads(args);
	if (pthread_create(&args->check_death, NULL, supervise_meal, args))
		error_exit(args, "pthread create failed");
	set_long(args, args->args_mutex, &args->start_simulation,
		gettime_us(args));
	set_bool(args, args->args_mutex, &args->all_philos_ready, true);
	while (i < args->nbr_philos)
	{
		safe_thread(args, args->philos[i].thread_id, JOIN);
		i++;
	}
}
