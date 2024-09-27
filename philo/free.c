/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:09:31 by maustel           #+#    #+#             */
/*   Updated: 2024/09/27 16:53:19 by maustel          ###   ########.fr       */
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
			// if (safe_mutex(&args->philos[i].count_mutex, DESTROY))
			// 	return ;
				// return (err(E_MUTEX));
			if (safe_mutex(&args->philos[i].full_mutex, DESTROY))
				return ;
				// return (err(E_MUTEX));
			if (safe_mutex(&args->philos[i].meal_time_mutex, DESTROY))
				return ;
				// return (err(E_MUTEX));
			if (safe_mutex(&args->forks[i].fork_mutex, DESTROY))
				return ;
				// return (err(E_MUTEX));
			i++;
		}
		free (args->philos);
		free (args->forks);
	}
	safe_mutex(&args->start_mutex, DESTROY);
	safe_mutex(&args->end_mutex, DESTROY);
	safe_mutex(&args->all_ready_mutex, DESTROY);
	safe_mutex(&args->nbr_ready_mutex, DESTROY);
	safe_mutex(&args->output_mutex, DESTROY);

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
		err_msg = "Error: Use timestamps major than 60ms!\n";
	else if (err_code == E_NPHILO)
		err_msg = "Error: Nbr Philo must be between 1 and 200.\n";
	else if (err_code == E_INPUT)
		err_msg = "Error: Input not a valid value\n";
	else if (err_code == E_NARGS)
		err_msg = "Error: Wrong amount of arguments!\n";
	else if (err_code == E_MUTEX)
		err_msg = "Error with Mutex!\n";
	else if (err_code == E_MALLOC)
		err_msg = "Error with malloc!\n";
	i = 0;
	while (err_msg[i])
		i++;
	write (2, err_msg, i);
	return (err_code);
}
