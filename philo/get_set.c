/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:12:08 by maustel           #+#    #+#             */
/*   Updated: 2024/09/13 14:16:34 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	simulation_finished(t_arguments *args)
{
	bool	finished;

	finished = false;
	finished = get_bool(args, args->args_mutex, args->end_simulation);
	return (finished);
}

void	set_bool(t_arguments *args, t_mtx mutex, bool *dest, bool value)
{
	safe_mutex(args, &mutex, LOCK);
	*dest = value;
	safe_mutex(args, &mutex, UNLOCK);
}

bool	get_bool(t_arguments *args, t_mtx mutex, bool dest)
{
	bool	ret;

	ret = false;
	safe_mutex(args, &mutex, LOCK);
	if (dest == true)
		ret = true;
	else
		ret = false;
	safe_mutex(args, &mutex, UNLOCK);
	return (ret);
}

void	set_long(t_arguments *args, t_mtx mutex, long *dest, long value)
{
	safe_mutex(args, &mutex, LOCK);
	*dest = value;
	safe_mutex(args, &mutex, UNLOCK);
}

bool	get_long(t_arguments *args, t_mtx mutex, long dest)
{
	long	ret;

	ret = false;
	safe_mutex(args, &mutex, LOCK);
	if (dest == true)
		ret = true;
	else
		ret = false;
	safe_mutex(args, &mutex, UNLOCK);
	return (ret);
}

