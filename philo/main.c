/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:19:22 by maustel           #+#    #+#             */
/*   Updated: 2024/10/01 15:27:31 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char	**argv)
{
	t_arguments	args;

	if (argc < 5 || argc > 6)
		return (err(E_NARGS));
	if (parsing(argc, argv, &args))
		return (1);
	if (args.nbr_must_eat == 0)
		return (0);
	if (data_init(&args))
		return (free_all(&args, 2));
	if (meal_start(&args))
		return (free_all(&args, 3));
	free_all(&args, 0);
	return (0);
}
