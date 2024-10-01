/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 15:33:16 by maustel           #+#    #+#             */
/*   Updated: 2024/10/01 10:15:51 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	safe_mutex(t_mtx *mutex, t_safe_mutex todo)
{
	if (todo == INIT)
		return (pthread_mutex_init(mutex, NULL));
	else if (todo == LOCK)
		return (pthread_mutex_lock(mutex));
	else if (todo == UNLOCK)
		return (pthread_mutex_unlock(mutex));
	else if (todo == DESTROY)
		return (pthread_mutex_destroy(mutex));
	else
		return (1);
	return (0);
}

