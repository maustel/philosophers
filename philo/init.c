/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 14:39:11 by maustel           #+#    #+#             */
/*   Updated: 2024/09/27 16:11:02 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/*
	assign two forks to each philo. which one to take first
	and which one to take second is important to avoid DEADLOCK.
	deadlock would be f.e. every philo takes left fork first and
	waits for the second -> everyone is blocked
	even philos take first right fork
	odd philos take first left fork
*/
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
static int	init_philos(t_arguments *args)
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
		// printf("%i %i %i\n", i, args->philos[i].first_fork->fork_id, args->philos[i].second_fork->fork_id);
		// if (safe_mutex(&args->philos[i].count_mutex, INIT))
		// 	return (err(E_MUTEX));
		if (safe_mutex(&args->philos[i].full_mutex, INIT))
			return (err(E_MUTEX));
		if (safe_mutex(&args->philos[i].meal_time_mutex, INIT))
			return (err(E_MUTEX));
		i++;
	}
	return (0);
}

static int	init_forks(t_arguments *args)
{
	int	i;

	i = 0;
	while (i < args->nbr_philos)
	{
		if (safe_mutex(&args->forks[i].fork, INIT))
			return (err(E_MUTEX));
		args->forks[i].fork_id = i;
		i++;
	}
	return (0);
}

static int	init_args_mutex(t_arguments *args)
{
	if (safe_mutex(&args->start_mutex, INIT))
		return (err(E_MUTEX));
	if (safe_mutex(&args->end_mutex, INIT))
		return (err(E_MUTEX));
	if (safe_mutex(&args->all_ready_mutex, INIT))
		return (err(E_MUTEX));
	if (safe_mutex(&args->nbr_ready_mutex, INIT))
		return (err(E_MUTEX));
	if (safe_mutex(&args->output_mutex, INIT))
		return (err(E_MUTEX));
	return (0);
}

/*
	initalize rest of the values as well as every philo and every fork

	./philo [number philos][time_to_die][time_to_eat][time_to_sleep][nbr_must_eat]
*/
int	data_init(t_arguments *args)
{
	args->end_simulation = false;
	args->all_philos_ready = false;
	args->nbr_philos_ready = 0;
	args->start_simulation = 0;
	if (init_args_mutex(args))
		return (1);
	args->philos = NULL;
	args->forks = NULL;
	args->philos = malloc(sizeof(t_philo) * args->nbr_philos);
	if (!args->philos)
		return (err(E_MALLOC));
	args->forks = malloc(sizeof(t_fork) * args->nbr_philos);
	if (!args->forks)
		return (err(E_MALLOC));
	if (init_forks(args))
		return (1);
	if (init_philos(args))
		return (1);
	return (0);
}
