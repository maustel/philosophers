/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 15:33:16 by maustel           #+#    #+#             */
/*   Updated: 2024/09/27 16:46:34 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	*safe_malloc(t_arguments *args, int bytes)
// {
// 	void	*ptr;

// 	ptr = malloc (bytes);
// 	if (!ptr)
// 		error_exit(args, "Error with malloc!");
// 	return (ptr);
// }

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
/*
	no create, because it would need 5 parameters
*/
// void	safe_thread(t_arguments *args, pthread_t thread_id, t_safe_thread todo)
// {
// 	if (todo == JOIN)
// 	{
// 		if (pthread_join(thread_id, NULL))
// 			return ;
// 			// return (0);
// 		// else
// 		// 	return (1);
// 	}
// 	if (todo == DETACH)
// 	{
// 		if (pthread_detach(thread_id))
// 			return ;
// 		// 	return (0);
// 		// else
// 		// 	return (1);
// 	}
// 	// else
// 	// 	return (0);
// 	(void) args;
// }
