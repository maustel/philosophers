/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:09:31 by maustel           #+#    #+#             */
/*   Updated: 2024/09/27 12:35:05 by maustel          ###   ########.fr       */
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

int	err(t_err err_code)
{
	char*	err_msg;
	int		i;

	err_msg = "Error: unknown error";
	if (err_code == E_TIMESTAMP)
		err_msg = "Error Use timestamps major than 60ms!\n";
	else if (err_code == E_NPHILO)
		err_msg = "Error: Nbr Philo must be between 1 and 200.\n";
	else if (err_code == E_INPUT)
		err_msg = "Error: Input not a valid value\n";
	else if (err_code == E_NARGS)
		err_msg = "Wrong amount of arguments!\n";
	i = 0;
	while (err_msg[i])
		i++;
	write (2, err_msg, i);
	return (err_code);
}