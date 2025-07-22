/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eat_routine.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/21 14:21:56 by dloustal      #+#    #+#                 */
/*   Updated: 2025/07/22 15:06:13 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_took_fork(t_philo *philo)
{
	pthread_mutex_lock(&(philo->params->print));
	printf("%lld %s%d has taken a fork%s\n",
		get_timestamp(philo->params->time),
		YELLOW, philo->index + 1, RESET);
	pthread_mutex_unlock(&(philo->params->print));
}

static void	print_eating(t_philo *philo)
{
	pthread_mutex_lock(&(philo->params->print));
	printf("%lld %s%d is eating%s\n", philo->last_meal, RED,
		philo->index + 1, RESET);
	pthread_mutex_unlock(&(philo->params->print));
}

static void	set_indices(t_philo *philo)
{
	philo->neighbor = (philo->index + 1) % philo->params->num_philos;
	if (philo->index != philo->params->num_philos - 1)
	{
		philo->first = philo->index;
		philo->second = philo->neighbor;
	}
	else
	{
		philo->first = 0;
		philo->second = philo->index;
	}
}

static void	*finish_eating(t_philo *philo, int first, int second)
{
	pthread_mutex_lock(&(philo->last_meal_mut));
	if (someone_died(philo->params))
		return (pthread_mutex_unlock(&(philo->last_meal_mut)),
			pthread_mutex_unlock(&(philo->forks[first]->mutex_fork)),
			pthread_mutex_unlock(&(philo->forks[second]->mutex_fork)), NULL);
	philo->last_meal = get_timestamp(philo->params->time);
	pthread_mutex_unlock(&(philo->last_meal_mut));
	print_eating(philo);
	usleep(philo->params->time_eat * 1000);
	if (someone_died(philo->params))
		return (pthread_mutex_unlock(&(philo->forks[first]->mutex_fork)),
			pthread_mutex_unlock(&(philo->forks[second]->mutex_fork)), NULL);
	pthread_mutex_lock(&(philo->x_eaten_mut));
	philo->times_eaten++;
	if (someone_died(philo->params))
		return (pthread_mutex_unlock(&(philo->x_eaten_mut)),
			pthread_mutex_unlock(&(philo->forks[first]->mutex_fork)),
			pthread_mutex_unlock(&(philo->forks[second]->mutex_fork)), NULL);
	pthread_mutex_unlock(&(philo->x_eaten_mut));
	pthread_mutex_unlock(&((philo->forks[first])->mutex_fork));
	pthread_mutex_unlock(&((philo->forks[second])->mutex_fork));
	return (NULL);
}

void	*eat_routine(void *data)
{
	t_philo	*philo;
	int		first;
	int		second;

	philo = (t_philo *)data;
	set_indices(philo);
	first = philo->first;
	second = philo->second;
	pthread_mutex_lock(&(philo->forks[first]->mutex_fork));
	if (someone_died(philo->params))
		return (pthread_mutex_unlock(&(philo->forks[first]->mutex_fork)), NULL);
	print_took_fork(philo);
	if (philo->index == philo->neighbor)
		return (inevitable_death(philo->params),
			pthread_mutex_unlock(&(philo->forks[first]->mutex_fork)), NULL);
	pthread_mutex_lock(&(philo->forks[second]->mutex_fork));
	if (someone_died(philo->params))
		return (pthread_mutex_unlock(&(philo->forks[first]->mutex_fork)),
			pthread_mutex_unlock(&(philo->forks[second]->mutex_fork)), NULL);
	print_took_fork(philo);
	finish_eating(philo, philo->first, philo->second);
	return (NULL);
}