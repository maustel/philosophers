/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 14:39:11 by maustel           #+#    #+#             */
/*   Updated: 2024/09/13 14:08:47 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/*assign two forks to each philo. which one to take first
and which one to take second is important to avoid DEADLOCK.
deadlock would be f.e. every philo takes left fork first and
waits for the second -> everyone is blocked */
static void	assign_forks(t_philo *philo, t_fork *forks, int position_philo)
{
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[position_philo];
		philo->second_fork = &forks[philo->id % philo->args->nbr_philos];
	}
	else
	{
		philo->first_fork = &forks[philo->id % philo->args->nbr_philos];
		philo->second_fork = &forks[position_philo];
	}
}

//initialize philo parameters
static void	init_philos(t_arguments *args)
{
	int	i;

	i = 0;
	while (i < args->nbr_philos)
	{
		args->philos[i].id = i + 1;
		args->philos[i].meals_count = 0;
		args->philos[i].full = false;
		args->philos[i].last_meal_time = 0;
		args->philos[i].args = args;
		assign_forks(&args->philos[i], args->forks, i);
		safe_mutex(args, &args->philos[i].philo_mutex, INIT);
		i++;
	}
}

/*
	initalize rest of the values as well as every philo and every fork

	./philo [number philos][time_to_die][time_to_eat][time_to_sleep][nbr_must_eat]
*/
void	data_init(t_arguments *args)
{
	int	i;

	i = 0;
	args->end_simulation = false;
	args->all_threads_ready = false;
	safe_mutex(args, &args->args_mutex, INIT);
	safe_mutex(args, &args->write_mutex, INIT);
	args->philos = NULL;
	args->forks = NULL;
	args->philos = safe_malloc(args, sizeof(t_philo) * args->nbr_philos);
	args->forks = safe_malloc(args, sizeof(t_fork) * args->nbr_philos);
	while (i < args->nbr_philos)
	{
		safe_mutex(args, &args->forks[i].fork, INIT);
		args->forks[i].fork_id = i;
		i++;
	}
	init_philos(args);
}
