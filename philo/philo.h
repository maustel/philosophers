/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maustel <maustel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:19:14 by maustel           #+#    #+#             */
/*   Updated: 2024/10/01 10:20:04 by maustel          ###   ########.fr       */
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
	int			nbr_philos;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			nbr_must_eat;
	long		start_simulation;//
	t_mtx		start_mutex;
	bool		end_simulation; //
	t_mtx		end_mutex;
	bool		all_philos_ready;//
	t_mtx		all_ready_mutex;
	long		nbr_philos_ready;//
	t_mtx		nbr_ready_mutex;
	pthread_t	check_death;
	// t_mtx		args_mutex;
	t_mtx		output_mutex;
	t_fork		*forks; //array to all our forks
	t_philo		*philos; //array to all our philos
}				t_arguments;

typedef struct s_fork
{
	t_mtx	fork_mutex;
	int		fork_id;
}				t_fork;

// ./philo 5 800 200 200 [6]
typedef struct s_philo
{
	int			id;
	long		meals_count;//
	// t_mtx		count_mutex;
	bool		full;//
	t_mtx		full_mutex;
	long		last_meal_time;//
	t_mtx		meal_time_mutex;
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	thread_id;
	// t_mtx		philo_mutex;
	t_arguments	*args;
}				t_philo;

typedef enum e_err
{
	E_NARGS = 1,
	E_TIMESTAMP,
	E_NPHILO,
	E_INPUT,
	E_MUTEX,
	E_THREAD,
	E_MALLOC,
	E_GETTIME
}			t_err;

typedef enum e_safe_mutex
{
	INIT,
	LOCK,
	UNLOCK,
	DESTROY
}				t_safe_mutex;

typedef enum e_philo_stauts
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIED
}				t_philo_status;

int	free_all(t_arguments *args, int err);
int		err(t_err err_code);
int		parsing(int argc, char **argv, t_arguments *args);
bool	safe_mutex(t_mtx *mutex, t_safe_mutex todo);
int		data_init(t_arguments *args);
int		meal_start(t_arguments *args);
long	gettime_us(void);
bool	simulation_finished(t_arguments *args);
void	exact_usleep(long sleeptime_us, t_arguments *args);
bool	get_bool(t_mtx *mutex, bool *value);
void	set_bool(t_mtx *mutex, bool *dest, bool value);
void	set_long(t_mtx *mutex, long *dest, long value);
long	get_long(t_mtx *mutex, long *dest);
void	increment(t_mtx *mutex, long *dest);
int		print_status(t_arguments *args, t_philo philo, t_philo_status status);
void	*supervise_meal(void *ar);
void	think(t_arguments *args, t_philo *philo);
