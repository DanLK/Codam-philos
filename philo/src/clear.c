/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clear.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/07 15:03:47 by dloustal      #+#    #+#                 */
/*   Updated: 2025/07/18 17:43:11 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	clear_philo(t_philo *philo)
{
	free(philo); //Need to free the other pointers as well
}

static void	clear_fork(t_fork *fork)
{
	// free((fork->mutex_fork));
	free(fork);
}

//Can make this function generic by passing as a parameter a function pointer 
void	clear_philo_arr(t_philo **philos, int index)
{
	int	i;

	i = 0;
	while (philos[i] && i < index)
	{
		clear_philo(philos[i]);
		i++;
	}
	free(philos);
}

void	clear_fork_arr(t_fork **forks, int index)
{
	int	i;

	i = 0;
	while (forks[i] && i < index)
	{
		clear_fork(forks[i]);
		i++;
	}
	free(forks);
}

void	clear_philo_data(t_param *params, t_philo **philos, t_fork **forks)
{
	clear_fork_arr(forks, params->num_philos);
	clear_philo_arr(philos, params->num_philos);
	free(params);
}

void	destroy_mutexes(t_param *pars, t_fork **fks, t_philo **philos)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&(pars->time_mutex));
	pthread_mutex_destroy(&(pars->dead));
	pthread_mutex_destroy(&(pars->print));
	while (i < pars->num_philos)
	{
		pthread_mutex_destroy(&(fks[i]->mutex_fork));
		pthread_mutex_destroy(&(philos[i]->last_meal_mut));
		pthread_mutex_destroy(&(philos[i]->x_eaten_mut));
		i++;
	}
}
