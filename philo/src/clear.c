/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clear.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/07 15:03:47 by dloustal      #+#    #+#                 */
/*   Updated: 2025/07/30 14:40:50 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//Can make this function generic by passing as a parameter a function pointer 
void	clear_philo_arr(t_philo **philos, int index)
{
	int	i;

	i = 0;
	while (philos[i] && i < index)
	{
		free(philos[i]);
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
		free(forks[i]);
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
