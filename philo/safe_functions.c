/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 15:33:16 by maustel           #+#    #+#             */
/*   Updated: 2024/09/13 15:11:26 by maustel          ###   ########.fr       */
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

void	safe_mutex(t_arguments *args, t_mtx *mutex, t_safe_mutex todo)
{
	if (todo == INIT)
	{
		if (pthread_mutex_init(mutex, NULL))
			error_exit(args, "pthread mutex init failed");
	}
	else if (todo == LOCK)
	{
		if (pthread_mutex_lock(mutex))
			error_exit(args, "pthread mutex lock failed");
	}
	else if (todo == UNLOCK)
	{
		if (pthread_mutex_unlock(mutex))
			error_exit(args, "pthread mutex unlock failed");
	}
	else if (todo == DESTROY)
	{
		if (pthread_mutex_destroy(mutex))
			error_exit(args, "pthread mutex destroy failed");
	}
	else
		error_exit(args, "Wrong input mutex_todo()");
}

void	safe_thread(t_arguments *args, pthread_t *thread_id,
		void* (*function)(void *), void *arg, t_safe_thread todo)
{
	if (todo == CREATE)
	{
		if (pthread_create(thread_id, NULL, function, arg))
			error_exit(args, "pthread create failed");
	}
	else if (todo == JOIN)
	{
		if (pthread_join(*thread_id, NULL))
			error_exit(args, "pthread join failed");
	}
	if (todo == DETACH)
	{
		if (pthread_detach(*thread_id))
			error_exit(args, "pthread detach failed");
	}
	else
		error_exit(args, "Wrong input thread_todo()");
}
