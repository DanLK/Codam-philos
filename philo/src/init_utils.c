/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/18 14:35:09 by dloustal      #+#    #+#                 */
/*   Updated: 2025/07/18 14:37:50 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*init_one_philo(t_param *params, t_fork **forks, int i)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	memset(philo, 0, sizeof(t_philo));
	philo->index = i;
	philo->times_eaten = 0;
	philo->last_meal = 0;
	philo->tid = 0;
	philo->params = params;
	pthread_mutex_init(&(philo->x_eaten_mut), NULL);
	pthread_mutex_init(&(philo->last_meal_mut), NULL);
	philo->forks = forks;
	return (philo);
}

t_fork	*init_one_fork(int index)
{
	t_fork	*fork;

	fork = malloc(sizeof(t_fork));
	if (!fork)
		return (NULL);
	fork->index = index;
	pthread_mutex_init(&(fork->mutex_fork), NULL);
	return (fork);
}
