/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine_checks.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/18 14:57:37 by dloustal      #+#    #+#                 */
/*   Updated: 2025/07/18 15:03:30 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	someone_died(t_param *params)
{
	bool	someone_died;

	pthread_mutex_lock(&(params->dead));
	someone_died = params->one_dead;
	pthread_mutex_unlock(&(params->dead));
	return (someone_died);
}

bool	inevitable_death(t_param *params)
{
	bool	dead;

	dead = false;
	while (!dead)
	{
		pthread_mutex_lock(&(params->dead));
		dead = params->one_dead;
		pthread_mutex_unlock(&(params->dead));
		if (!dead)
			usleep(500);
		else
			return (true);
	}
	return (false);
}

bool	completed_meals(t_philo	*philo)
{
	bool	finished_meals;

	if (philo->params->num_cycles == -1)
		return (false);
	pthread_mutex_lock(&(philo->x_eaten_mut));
	finished_meals = philo->times_eaten >= philo->params->num_cycles;
	pthread_mutex_unlock(&(philo->x_eaten_mut));
	return (finished_meals);
}

//For the monitoring routine
bool	philos_need_to_eat(t_philo	**philos, int num)
{
	int		i;
	int		times_eaten;

	i = 0;
	while (i < num)
	{
		pthread_mutex_lock(&(philos[i]->x_eaten_mut));
		times_eaten = philos[i]->times_eaten;
		pthread_mutex_unlock(&(philos[i]->x_eaten_mut));
		if (times_eaten < philos[i]->params->num_cycles
			|| philos[i]->params->num_cycles == -1)
			return (true);
		i++;
	}
	return (false);
}

bool	time_expired(t_philo **philos, int index)
{
	long long	current_time;
	bool		time_expired;

	current_time = get_timestamp(philos[index]->params->time);
	pthread_mutex_lock(&(philos[index]->last_meal_mut));
	time_expired = current_time
		- philos[index]->last_meal > philos[index]->params->time_die;
	pthread_mutex_unlock(&(philos[index]->last_meal_mut));
	return (time_expired);
}
