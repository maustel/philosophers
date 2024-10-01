/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meal.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:40:39 by maustel           #+#    #+#             */
/*   Updated: 2024/10/01 15:50:13 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	try to make system more fair
	if nbr is even ->force even philo to wait for 30ms before doing anything
	otherwise, some philos would eat twice in a row without thinking
	and other philos would starve
	if nbr is odd -> force odd philos to start thinking
*/
static void	asynchronizer(t_philo *philo)
{
	if (philo->nbr_philos % 2 == 0)
	{
		if (philo->id % 2 == 0)
			exact_usleep(3000, philo->args);
	}
	else
	{
		if (philo->id % 2 != 0)
			think(philo->args, philo);
	}
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
static void	*meal_simulation(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *) ph;
	while (!get_bool(&philo->args->all_ready_mutex,
			&philo->args->all_philos_ready))
		usleep(10);
	increment(&philo->args->nbr_ready_mutex,
		&philo->args->nbr_philos_ready);
	asynchronizer(philo);
	while (!simulation_finished(philo->args)
		&& !get_bool(&philo->full_mutex, &philo->full))
	{
		if (eat(philo->args, philo))
			return (NULL);
		sleeping(philo->args, *philo);
		think(philo->args, philo);
	}
	return (NULL);
}

/*
	each philo remains in waitingloop until all of them are created
*/
int	create_philo_threads(t_arguments *args)
{
	int	i;

	i = 0;
	while (i < args->nbr_philos)
	{
		if (pthread_create(&args->philos[i].thread_id, NULL,
				meal_simulation, &args->philos[i]))
			return (err(E_THREAD));
		i++;
	}
	return (0);
}

/*
	create one thread for each philo
	only if all threads are made and ready we start simulation
	join is for waiting and also for cleaning up in the end
*/
int	meal_start(t_arguments *args)
{
	int	i;

	i = -1;
	if (args->nbr_philos == 1)
	{
		if (pthread_create(&args->philos[0].thread_id, NULL,
				one_philo, &args->philos[0]))
			return (err(E_THREAD));
	}
	else if (create_philo_threads(args))
		return (1);
	if (pthread_create(&args->check_death, NULL, supervise_meal, args))
		return (err(E_THREAD));
	set_long(&args->start_mutex, &args->start_simulation,
		gettime_us());
	set_bool(&args->all_ready_mutex, &args->all_philos_ready, true);
	while (++i < args->nbr_philos)
	{
		if (pthread_join(args->philos[i].thread_id, NULL))
			return (err(E_THREAD));
	}
	set_bool(&args->end_mutex, &args->end_simulation, true);
	if (pthread_join(args->check_death, NULL))
		return (err(E_THREAD));
	return (0);
}
