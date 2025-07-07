/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/04 16:50:26 by dloustalot    #+#    #+#                 */
/*   Updated: 2025/07/07 16:40:38 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_param
{
	int	num_philos;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	num_cycles;
}		t_param;

typedef struct s_philo
{
	int				index;
	pthread_mutex_t	mutex_fork;
	int				times_eaten;
	int				total_philos;
	int				time_eat;
	pthread_t		tid;
}		t_philo;

//Init
t_param	*parse_params(int argc, char **argv);
t_philo	*init_one_philo(t_param *params, int i);
t_philo	**init_philos(t_param *params);

//Clears
void	clear_philo_arr(t_philo **philos, int index);

//Routines
void	*simple_routine(void *data);
void	*eat_routine(void *data);

//DEbug
void	print_philos(t_philo **philos, t_param *params);

#endif