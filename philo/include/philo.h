/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/04 16:50:26 by dloustalot    #+#    #+#                 */
/*   Updated: 2025/07/08 15:29:04 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>

# define YELLOW "\e[1;33m"
# define YELlOW_B "\e[1;43m"
# define PURPLE "\e[1;94m"
# define PURPLE_B "\e[1;104m"
# define RED "\e[1;31m"
# define RESET "\e[0m"

typedef struct s_param
{
	int	num_philos;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	num_cycles;
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
//	int				total_philos;
//	int				time_eat;
	pthread_t		tid;
	t_param			*params;
	t_fork			**forks;
}		t_philo;


//Init
t_param	*parse_params(int argc, char **argv);
t_philo	*init_one_philo(t_param *params, t_fork **forks, int i);
t_philo	**init_philos(t_param *params, t_fork **forks);
t_fork	*init_one_fork(int index);
t_fork	**init_forks(t_param *params);

//Clears
void	clear_philo_arr(t_philo **philos, int index);
void	clear_fork_arr(t_fork **forks, int index);

//Routines
void	*simple_routine(void *data);
void	*eat_routine(void *data);

//DEbug
void	print_philos(t_philo **philos, t_param *params);

#endif