/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meal.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:40:39 by maustel           #+#    #+#             */
/*   Updated: 2024/10/01 10:17:46 by maustel          ###   ########.fr       */
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

static void	sleeping(t_arguments *args, t_philo philo)
{
	if (simulation_finished(args))
		return ;
	print_status(args, philo, SLEEP);
	exact_usleep(args->time_to_sleep, args);
}

// bool	philo_full(t_arguments *args, t_philo philo)
// {
// 	long	meals;

// 	meals = 0;
// 	if (args->nbr_must_eat > 0)
// 	{
// 		meals = get_long(&philo.count_mutex, &philo.meals_count);
// 		if (args->nbr_must_eat == meals)
// 			return (true);
// 	}
// 	return (false);
// }

/*
	takes both forks and print status
	when he has both forks, starts to eat, print status
	update last_meal_time
	update meals_count
	if philo is full, update full=true
	usleep(time_to_eat)
	release forks
*/
static int	eat(t_arguments *args, t_philo *philo)
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

/*
	try to make system more fair
	if nbr is even ->force even philo to wait for 30ms before doing anything
	otherwise, some philos would eat twice in a row without thinking
	and other philos would starve
	if nbr is odd -> force odd philos to start thinking
*/
void	asynchronizer(t_philo *philo)
{
	if (philo->args->nbr_philos % 2 == 0)
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
void	*meal_simulation(void *ph)
{
	t_philo *philo;

	philo = (t_philo *) ph;
	while (!get_bool(&philo->args->all_ready_mutex,
			&philo->args->all_philos_ready))
		usleep(10);
	increment(&philo->args->nbr_ready_mutex,
		&philo->args->nbr_philos_ready);
	asynchronizer(philo);
	while (!simulation_finished(philo->args) &&
		!get_bool(&philo->full_mutex, &philo->full))
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
void	*test(void* a)
{
	void* ptr = a;

	ptr = NULL;

	return (ptr);
}

int	meal_start(t_arguments *args)
{
	int	i;

	i = 0;
	if (args->nbr_philos == 1)
	{
		if (pthread_create(&args->philos[0].thread_id, NULL,
			one_philo, &args->philos[i]))
				return (err(E_THREAD));
	}
	else if (create_philo_threads(args))
			return (1);
	// if (pthread_create(&args->check_death, NULL, test, NULL))
	if (pthread_create(&args->check_death, NULL, supervise_meal, args))
		return (err(E_THREAD));
	set_long(&args->start_mutex, &args->start_simulation,
		gettime_us());
	set_bool(&args->all_ready_mutex, &args->all_philos_ready, true);
	while (i < args->nbr_philos)
	{
		if (pthread_join(args->philos[i].thread_id, NULL))
			return (err(E_THREAD));
		i++;
	}
	set_bool(&args->end_mutex, &args->end_simulation, true);
	if (pthread_join(args->check_death, NULL))
		return (err(E_THREAD));
	return (0);
}
