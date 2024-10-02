/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 14:34:35 by maustel           #+#    #+#             */
/*   Updated: 2024/10/02 11:06:16 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*Error should occur when input i negative number, inpout > INT_MAX, input not
legit number, imestamps smaller than 60ms, number of philos > 200 */
static int	philo_atoi(char *str)
{
	long long	nbr;
	int			minus;
	int			len;

	while ((*str < 14 && *str > 8) || *str == 32)
		str++;
	minus = 1;
	if (*str == '+')
		str++;
	if (*str == '-')
		return (-1);
	nbr = 0;
	if (*str < '0' || *str > '9')
		return (-1);
	len = 0;
	while (str && '0' <= *str && *str <= '9')
	{
		nbr = nbr * 10 + (*str - '0');
		str++;
		len++;
	}
	if (len > 10 || nbr > INT_MAX)
		return (-1);
	return ((int)(nbr * minus));
}

/*
	usleep wants microseconds [us] --> us = ms * 1000
*/
int	parsing(int argc, char **argv, t_arguments *args)
{
	args->nbr_philos = philo_atoi(argv[1]);
	args->time_to_die = philo_atoi(argv[2]) * 1000;
	args->time_to_eat = philo_atoi(argv[3]) * 1000;
	args->time_to_sleep = philo_atoi(argv[4]) * 1000;
	if (args->nbr_philos < 0 || args->time_to_die < 0 || args->time_to_eat < 0
		|| args->time_to_sleep < 0)
		return (err(E_INPUT));
	if (argc == 6)
	{
		args->nbr_must_eat = philo_atoi(argv[5]);
		if (args->nbr_must_eat < 0)
			return (err(E_INPUT));
	}
	else
		args->nbr_must_eat = -1;
	if (args->time_to_die < 6e4 || args->time_to_eat < 6e4
		|| args->time_to_sleep < 6e4)
		return (err(E_TIMESTAMP));
	if (args->nbr_philos <= 0 || args->nbr_philos > 200)
		return (err(E_NPHILO));
	return (0);
}
