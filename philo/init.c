/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 14:39:11 by maustel           #+#    #+#             */
/*   Updated: 2024/09/06 17:12:40 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	assign_forks(t_philo *philos, t_fork *forks, int position)
// {

// }

static void	init_philos(t_arguments *args, int i)
{
	args->philos[i].id = i + 1;
	args->philos[i].meals_count = 0;
	args->philos[i].full = false;
	args->philos[i].last_meal_time = 0;
	args->philos[i].args = args;

	//assign forks(args->philos[i], args->forks, i)

}

void	data_init(t_arguments *args)
{
	int	i;

	i = 0;
	args->end_simulation = false;
	args->philos = safe_malloc(sizeof(t_philo) * args->nbr_philos);
	args->forks = safe_malloc(sizeof(t_fork) * args->nbr_philos);
	while (i < args->nbr_philos)
	{
		//mutex init forks
		if (pthread_mutex_init(&args->forks[i].fork, NULL) != 0)
			error_exit("pthread init failed");
		args->forks[i].fork_id = i;
		init_philos(args, i);
		i++;
	}
}