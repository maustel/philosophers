/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:09:31 by maustel           #+#    #+#             */
/*   Updated: 2024/09/06 12:57:36 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_arguments *args)
{
	if (args)
		free (args);
}
void	error_exit(const char *error)
{
	printf("%s \n", error);
	exit (1);
}
