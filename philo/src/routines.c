/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routines.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/07 15:43:39 by dloustal      #+#    #+#                 */
/*   Updated: 2025/07/18 15:37:11 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_thinking(t_philo	*philo)
{
	pthread_mutex_lock(&(philo->params->print));
	printf("%lld %s%d is thinking%s\n", get_timestamp(philo->params->time),
		GRAY, philo->index + 1, RESET);
	pthread_mutex_unlock(&(philo->params->print));
}

void	*life_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (get_start_time() < philo->params->time)
		usleep(30);
	if (philo->index % 2 == 1)
		usleep(1000);
	while (!completed_meals(philo))
	{
		if (someone_died(philo->params))
			break ;
		eat_routine(data);
		if (completed_meals(philo) || someone_died(philo->params))
			break ;
		sleep_routine(data);
		if (someone_died(philo->params))
			break ;
		print_thinking(philo);
		usleep(philo->params->time_think * 1000);
		if (someone_died(philo->params))
			break ;
	}
	return (NULL);
}

void	*sleep_routine(void *data)
{
	t_philo	*philo;
	int		index;

	philo = (t_philo *)data;
	index = philo->index;
	if (someone_died(philo->params))
		return (NULL);
	pthread_mutex_lock(&(philo->params->print));
	printf("%lld %s%d is sleeping%s\n", get_timestamp(philo->params->time),
		BLUE, index + 1, RESET);
	pthread_mutex_unlock(&(philo->params->print));
	usleep(philo->params->time_sleep * 1000);
	if (someone_died(philo->params))
		return (NULL);
	return (NULL);
}

static void	print_dead(t_monitor *moni, int i)
{
	pthread_mutex_lock(&(moni->philos[0]->params->print));
	printf("%lld %s%d died%s\n", get_timestamp(moni->philos[0]->params->time),
		GREEN, i, RESET);
	pthread_mutex_unlock(&(moni->philos[0]->params->print));
}

void	*monitor_routine(void *data)
{
	t_monitor	*monitor;
	int			i;

	monitor = (t_monitor *)data;
	while (philos_need_to_eat(monitor->philos, monitor->num_philos)
		&& !someone_died(monitor->philos[0]->params))
	{
		i = 0;
		while (i < monitor->num_philos)
		{
			if (time_expired(monitor->philos, i++))
			{
				pthread_mutex_lock(&(monitor->philos[0]->params->dead));
				monitor->philos[0]->params->one_dead = true;
				pthread_mutex_unlock(&(monitor->philos[0]->params->dead));
				usleep(200);
				print_dead(monitor, i);
				break ;
			}
		}
	}
	return (NULL);
}

// void	*simple_routine(void *data)
// {
// 	pthread_t	tid;
// 	t_philo		*philo;

// 	philo = (t_philo *)data;
// 	tid = pthread_self();
// 	printf("Philo #%d of %d is a thread [%ld]\n\n", philo->index,
// (philo->params->num_philos), tid);
// 	return (NULL);
// }