/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:19:22 by maustel           #+#    #+#             */
/*   Updated: 2024/09/06 14:39:54 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



int	main(int argc, char	**argv)
{
	t_arguments args;

	if (argc < 5 || argc > 6)
	{
		error_exit("Wrong amount of arguments!");
	}
	parsing(argc, argv, &args);

	// data_init(&args);
	// dinner_start(args);
	// clean (args); 	//philos full or one died

	return (0);
}
