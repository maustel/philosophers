/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:19:14 by maustel           #+#    #+#             */
/*   Updated: 2024/09/12 17:59:45 by maustel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <limits.h>
#include <sys/time.h>
#include <stdbool.h>

typedef pthread_mutex_t	t_mtx;
typedef struct s_fork	t_fork;
typedef struct s_philo	t_philo;

typedef struct s_arguments
{
	int		nbr_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		nbr_must_eat;
	long	start_simulation;
	bool	end_simulation; // a philo dies or all philos are full
	bool	all_threads_ready;
	t_mtx	args_mutex;
	t_fork	*forks; //array to all our forks
	t_philo	*philos; //array to all our philos
}				t_arguments;

typedef struct s_fork
{
	t_mtx	fork;
	int		fork_id;
}				t_fork;

// ./philo 5 800 200 200 [6]
typedef struct s_philo
{
	int			id;
	long		meals_count;
	bool		full;
	long		last_meal_time;
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	thread_id;
	t_arguments	*args;
}				t_philo;

typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND
}				t_time_code;

// void	free_all(t_arguments *args);
void	error_exit(t_arguments *args, char *error);
void	parsing(int argc, char **argv, t_arguments *args);
void	*safe_malloc(t_arguments *args, int bytes);
void	data_init(t_arguments *args);
void	meal_start(t_arguments *args);
long	gettime(t_arguments *args, t_time_code time_code);
bool	simulation_finished(t_arguments *args);
