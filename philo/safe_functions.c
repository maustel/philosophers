/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 15:33:16 by maustel           #+#    #+#             */
/*   Updated: 2024/09/06 15:34:53 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*safe_malloc(int bytes)
{
	void	*ptr;

	ptr = malloc (bytes);
	if (!ptr)
		error_exit("Error with malloc!");
	return (ptr);
}