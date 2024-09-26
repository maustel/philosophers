/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:09:31 by maustel           #+#    #+#             */
/*   Updated: 2024/09/26 14:28:21 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_arguments *args)
{
	int	i;

	i = 0;
	if (args->philos && args->forks)
	{
		while (i < args->nbr_philos)
		{
			safe_mutex(args, &args->philos[i].count_mutex, DESTROY);
			safe_mutex(args, &args->philos[i].full_mutex, DESTROY);
			safe_mutex(args, &args->philos[i].meal_time_mutex, DESTROY);
			safe_mutex(args, &args->forks[i].fork, DESTROY);
			i++;
		}
		free (args->philos);
		free (args->forks);
	}
	safe_mutex(args, &args->start_mutex, DESTROY);
	safe_mutex(args, &args->end_mutex, DESTROY);
	safe_mutex(args, &args->all_ready_mutex, DESTROY);
	safe_mutex(args, &args->nbr_ready_mutex, DESTROY);
	safe_mutex(args, &args->output_mutex, DESTROY);
	// safe_mutex(args, &args->args_mutex, DESTROY);
}

void	error_exit(t_arguments *args, char *error)
{
	if (args)
		free_all(args);
	printf("\033[31;1mError!\n%s\033[0m \n", error);
	exit (1);
}
