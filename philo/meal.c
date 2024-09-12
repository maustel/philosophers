/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meal.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:40:39 by maustel           #+#    #+#             */
/*   Updated: 2024/09/12 17:59:28 by maustel          ###   ########.fr       */
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



/*
	check if args->all_threads_ready - flag is already set to true
	(is set in meal_start)
*/
bool	philos_ready(t_arguments *args)
{
	bool	ready;

	ready = false;
	pthread_mutex_lock(&args->args_mutex);
	if (args->all_threads_ready == true)
		ready = true;
	else
		ready = false;
	pthread_mutex_unlock(&args->args_mutex);
	return (ready);
}


/*
	synchronize beginning of simulation
	-> wait for all philos
	->every philo starts simultaneously
	wait for all threads -> waitingloop
*/
void	*meal_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (!philos_ready(philo->args))
		usleep(10);
	return (NULL);
	while (!simulation_finished(philo->args))
	{
		//1) philo full? -> break
		//2) eat
		//3) sleep ->write_status + better_usleep
		//4) think
	}
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
		if (pthread_create(&args->philos[i].thread_id, NULL, meal_simulation,
				&args->philos[i]))
			error_exit(args, "error with pthread_creates");
		i++;
	}
}

/*
	create one thread for each philo
	only if all threads are made and ready we start simulation
*/
void	meal_start(t_arguments *args)
{
	int	i;

	if (args->nbr_must_eat == 0)
		return ;
	else if (args->nbr_philos == 1)
		;//TODO
	else
		create_philo_threads(args);
	args->start_simulation = gettime(args, MILLISECOND);
	pthread_mutex_lock(&args->args_mutex);
	args->all_threads_ready = true;
	pthread_mutex_unlock(&args->args_mutex);
	i = 0;
	while (i < args->nbr_philos)
	{
		if (pthread_join(args->philos[i].thread_id, NULL))
			error_exit(args, "Error pthread_join");
		i++;
	}
}
