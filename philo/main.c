/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:19:22 by maustel           #+#    #+#             */
/*   Updated: 2024/09/27 12:35:33 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	test_function(t_arguments *args)
{
	int	i;

	printf("\nnbr_philos: %d\n", args->nbr_philos);
	printf("time_to_die: %d\n", args->time_to_die/1000);
	printf("time_to_eat: %d\n", args->time_to_eat/1000);
	printf("time_to_sleep: %d\n", args->time_to_sleep/1000);
	printf("nbr_must_eat: %d\n", args->nbr_must_eat);
	printf("start_simulation: %ld\n", args->start_simulation);
	printf("end_simulation: %d\n\n", args->end_simulation);
	i = 0;
	while (i < args->nbr_philos)
	{
		printf("philo id: %d\n", args->philos[i].id);
		printf("meals_count: %ld\n", args->philos[i].meals_count);
		printf("full: %d\n", args->philos[i].full);
		printf("last_meal_time: %ld\n", args->philos[i].last_meal_time);
		printf("first_fork: %d\n", args->philos[i].first_fork->fork_id);
		printf("second_fork: %d\n", args->philos[i].second_fork->fork_id);
		printf("\n---------------------------\n");
		i++;
	}
}

int	main(int argc, char	**argv)
{
	t_arguments	args;

	if (argc < 5 || argc > 6)
		return (err(E_NARGS));
	if (parsing(argc, argv, &args))
		return (1);
	if (data_init(&args))
		return (2);
	meal_start(&args);
	// test_function(&args);
	free_all(&args);
	return (0);

}

/*
parsing()
ERR_TOOMANYARGC = 1
ERR_FILENOTEXISTS = 2
ERR_WRONGCHARDETECTED = 3
ERR_TOOMANYWHITESPACES = 4
*/