/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 14:34:35 by maustel           #+#    #+#             */
/*   Updated: 2024/09/07 12:26:56 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


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
			error_exit(NULL, "Only positive numbers are valid!");
	nbr = 0;
	if (*str < '0' || *str > '9')
		error_exit(NULL, "Input is not a legit number!");
	len = 0;
	while (str && '0' <= *str && *str <= '9')
	{
		nbr = nbr * 10 + (*str - '0');
		str++;
		len++;
	}
	if (len > 10 || nbr > INT_MAX)
		error_exit(NULL, "Value too big, INT_MAX is limit!");
	return ((int)(nbr * minus));
}
/*
	usleep wants microseconds [us] --> us = ms * 1000
*/

void	parsing(int argc, char **argv, t_arguments *args)
{
	args->nbr_philos = philo_atoi(argv[1]);
	args->time_to_die = philo_atoi(argv[2]) * 1000;
	args->time_to_eat = philo_atoi(argv[3]) * 1000;
	args->time_to_sleep = philo_atoi(argv[4]) * 1000;
	if (argc == 6)
		args->nbr_must_eat = philo_atoi(argv[5]);
	if (args->time_to_die < 6e4 || args->time_to_eat < 6e4 ||
		 args->time_to_sleep < 6e4)
		{
			error_exit(NULL, "Use timestamps major than 60ms!\n");
		}
	if (args->nbr_philos <= 0 || args->nbr_philos > 200)
		error_exit(NULL, "Number of philos must be between 1 and 200!");
}