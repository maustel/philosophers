/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 14:39:11 by maustel           #+#    #+#             */
/*   Updated: 2024/09/07 11:57:38 by maustel          ###   ########.fr       */
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
		i++;
	}
}

/*initalize rest of the values as well as every philo and every fork*/
void	data_init(t_arguments *args)
{
	int	i;

	i = 0;
	args->end_simulation = false;
	args->philos = safe_malloc(sizeof(t_philo) * args->nbr_philos);
	args->forks = safe_malloc(sizeof(t_fork) * args->nbr_philos);
	while (i < args->nbr_philos)
	{
		if (pthread_mutex_init(&(args->forks[i].fork), NULL) != 0)
			error_exit("pthread init failed");
		args->forks[i].fork_id = i;
		i++;
	}
	init_philos(args);
}
