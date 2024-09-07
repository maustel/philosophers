/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 15:33:16 by maustel           #+#    #+#             */
/*   Updated: 2024/09/07 12:45:13 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*safe_malloc(t_arguments *args, int bytes)
{
	void	*ptr;

	ptr = malloc (bytes);
	if (!ptr)
		error_exit(args, "Error with malloc!");
	return (ptr);
}
