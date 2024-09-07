/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:09:31 by maustel           #+#    #+#             */
/*   Updated: 2024/09/07 12:24:20 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_arguments *args)
{
	if (args->philos)
		free (args->philos);
	if (args->forks)
		free (args->forks);
}
void	error_exit(t_arguments *args, char *error)
{
	if (args)
		free_all(args);
	printf("\033[31;1mError!\n%s\033[0m \n", error);
	exit (1);
}
