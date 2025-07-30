/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/21 14:25:14 by dloustal      #+#    #+#                 */
/*   Updated: 2025/07/30 14:43:01 by dloustal      ########   odam.nl         */
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

void	print_sleeping(t_philo *philo)
{
	pthread_mutex_lock(&(philo->params->print));
	if (someone_died(philo->params))
	{
		pthread_mutex_unlock(&(philo->params->print));
		return ;
	}
	printf("%lld %s%d is sleeping%s\n", get_timestamp(philo->params->time),
		BLUE, philo->index + 1, RESET);
	pthread_mutex_unlock(&(philo->params->print));
}

void	print_thinking(t_philo *philo)
{
	pthread_mutex_lock(&(philo->params->print));
	if (someone_died(philo->params))
	{
		pthread_mutex_unlock(&(philo->params->print));
		return ;
	}
	printf("%lld %s%d is thinking%s\n", get_timestamp(philo->params->time),
		GRAY, philo->index + 1, RESET);
	pthread_mutex_unlock(&(philo->params->print));
}
