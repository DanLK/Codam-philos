/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/04 16:50:26 by dloustalot    #+#    #+#                 */
/*   Updated: 2025/07/22 14:34:56 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>

# define YELLOW "\e[1;33m"
# define YELlOW_B "\e[1;43m"
# define PURPLE "\e[1;35m"
# define PURPLE_B "\e[1;45m"
# define RED "\e[1;31m"
# define BLUE "\e[1;34m"
# define GRAY "\e[1;37m"
# define GREEN "\e[1;32m"
# define RESET "\e[0m"

typedef struct s_param
{
	int				num_philos;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				time_think;
	int				num_cycles;
	long long		time;
	pthread_mutex_t	time_mutex;
	bool			one_dead;
	pthread_mutex_t	dead;
	pthread_mutex_t	print;
}		t_param;

typedef struct s_fork
{
	int				index;
	pthread_mutex_t	mutex_fork;
}		t_fork;

typedef struct s_philo
{
	int				index;
	int				times_eaten;
	long long		last_meal;
	pthread_mutex_t	x_eaten_mut;
	pthread_mutex_t	last_meal_mut;
	pthread_t		tid;
	t_param			*params;
	t_fork			**forks;
	int				first;
	int				second;
	int				neighbor;
}		t_philo;


typedef struct s_monitor
{
	t_philo		**philos;
	int			num_philos;
	pthread_t	tid;
}		t_monitor;

typedef struct s_data
{
	t_param		*params;
	t_fork		**forks;
	t_philo		**philos;
	t_monitor	*monitor;
}		t_data;

//Init
t_param		*parse_params(int argc, char **argv);
t_philo		*init_one_philo(t_param *params, t_fork **forks, int i);
t_philo		**init_philos(t_param *params, t_fork **forks);
t_fork		*init_one_fork(int index);
t_fork		**init_forks(t_param *params);
t_monitor	*init_monitor(t_philo **philos, int num_philos);

//Clears
void		clear_philo_arr(t_philo **philos, int index);
void		clear_fork_arr(t_fork **forks, int index);
void		clear_philo_data(t_param *params, t_philo **philos, t_fork **forks);
void		destroy_mutexes(t_param *pars, t_fork **fks, t_philo **philos);

//Routines
void		*eat_routine(void *data);
void		*life_routine(void *data);
void		*sleep_routine(void *data);
void		*monitor_routine(void *data);

// Routine utils
bool	inevitable_death(t_param *params);
bool	someone_died(t_param *params);

//Utils
long long	get_start_time(void);
long long	get_timestamp(long long start_time);
int			ft_atoi(const char *nptr);
bool		valid_params(int argc, char **argv);
void		ft_usleep(long ms, t_param *params);

//DEbug
void		print_philos(t_philo **philos, t_param *params);

#endif