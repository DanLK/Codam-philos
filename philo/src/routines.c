/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routines.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/07 15:43:39 by dloustal      #+#    #+#                 */
/*   Updated: 2025/07/17 19:20:20 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	someone_has_died(t_param *params)
{
	bool	someone_died;
	
	pthread_mutex_lock(&(params->dead));
	someone_died = params->one_dead;
	pthread_mutex_unlock(&(params->dead));
	return (someone_died);
}

void	*eat_routine(void *data)
{
	t_philo	*philo;
	int		first;
	int		second;
	int		i_neighbor;

	philo = (t_philo *)data;
	i_neighbor = (philo->index + 1) % philo->params->num_philos;
	if (philo->index != philo->params->num_philos - 1)
	{
		first = philo->index;
		second = i_neighbor;
	}
	else
	{
		first = 0;
		second = philo->index;
	}
	pthread_mutex_lock(&(philo->forks[first]->mutex_fork));
	if (someone_has_died(philo->params))
		return (pthread_mutex_unlock(&(philo->forks[first]->mutex_fork)), NULL);
	pthread_mutex_lock(&(philo->params->print));
	printf("%lld %s%d has taken a fork%s\n", get_timestamp(philo->params->time), YELLOW, philo->index + 1, RESET);
	pthread_mutex_unlock(&(philo->params->print));
	if (philo->index == i_neighbor)
		return (pthread_mutex_unlock(&(philo->forks[first]->mutex_fork)), NULL);
	pthread_mutex_lock(&(philo->forks[second]->mutex_fork));
	if (someone_has_died(philo->params))
		return (pthread_mutex_unlock(&(philo->forks[first]->mutex_fork)),
			pthread_mutex_unlock(&(philo->forks[second]->mutex_fork)), NULL);
	pthread_mutex_lock(&(philo->params->print));
	printf("%lld %s%d has taken a fork%s\n", get_timestamp(philo->params->time), YELLOW, philo->index + 1, RESET);
	pthread_mutex_unlock(&(philo->params->print));
	pthread_mutex_lock(&(philo->last_meal_mut));
	if (someone_has_died(philo->params))
		return (pthread_mutex_unlock(&(philo->last_meal_mut)), pthread_mutex_unlock(&(philo->forks[first]->mutex_fork)),
			pthread_mutex_unlock(&(philo->forks[second]->mutex_fork)), NULL);
	philo->last_meal = get_timestamp(philo->params->time);
	pthread_mutex_lock(&(philo->params->print));
	printf("%lld %s%d is eating%s\n", philo->last_meal, RED, philo->index + 1, RESET);
	pthread_mutex_unlock(&(philo->last_meal_mut));
	pthread_mutex_unlock(&(philo->params->print));
	usleep(philo->params->time_eat * 1000);
	if (someone_has_died(philo->params))
		return (pthread_mutex_unlock(&(philo->forks[first]->mutex_fork)),
			pthread_mutex_unlock(&(philo->forks[second]->mutex_fork)), NULL);
	pthread_mutex_lock(&(philo->x_eaten_mut));
	philo->times_eaten++;
	if (someone_has_died(philo->params))
		return (pthread_mutex_unlock(&(philo->x_eaten_mut)), pthread_mutex_unlock(&(philo->forks[first]->mutex_fork)),
			pthread_mutex_unlock(&(philo->forks[second]->mutex_fork)), NULL);
	pthread_mutex_unlock(&(philo->x_eaten_mut));
	pthread_mutex_unlock(&((philo->forks[first])->mutex_fork));
	pthread_mutex_unlock(&((philo->forks[second])->mutex_fork));
	return (NULL);
}

static bool	completed_meals(t_philo	*philo)
{
	bool	finished_meals;

	if (philo->params->num_cycles == -1)
		return (false);
	pthread_mutex_lock(&(philo->x_eaten_mut));
	finished_meals = philo->times_eaten >= philo->params->num_cycles;
	pthread_mutex_unlock(&(philo->x_eaten_mut));
	return (finished_meals);
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
		if (someone_has_died(philo->params))
			break ;
		eat_routine(data);
		if (completed_meals(philo) || someone_has_died(philo->params))
		break ;
		sleep_routine(data);
		if (someone_has_died(philo->params))
			break ;
		pthread_mutex_lock(&(philo->params->print));
		printf("%lld %s%d is thinking%s\n", get_timestamp(philo->params->time), GRAY, philo->index + 1, RESET);
		pthread_mutex_unlock(&(philo->params->print));
		usleep(philo->params->time_think * 1000);
		if (someone_has_died(philo->params))
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
	if (someone_has_died(philo->params))
		return (NULL);
	pthread_mutex_lock(&(philo->params->print));
	printf("%lld %s%d is sleeping%s\n", get_timestamp(philo->params->time), BLUE, index + 1, RESET);
	pthread_mutex_unlock(&(philo->params->print));
	usleep(philo->params->time_sleep * 1000);
	if (someone_has_died(philo->params))
		return (NULL);
	return (NULL);
}

static bool philos_need_to_eat(t_philo	**philos, int num)
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

static bool	time_expired(t_philo **philos, int index)
{
	long long	current_time;
	bool		time_expired;

	current_time = get_timestamp(philos[index]->params->time);
	pthread_mutex_lock(&(philos[index]->last_meal_mut));
	time_expired = current_time - philos[index]->last_meal > philos[index]->params->time_die;
	pthread_mutex_unlock(&(philos[index]->last_meal_mut));
	return(time_expired);
}

void	*monitor_routine(void *data)
{
	t_monitor	*monitor;
	int			index;
	
	monitor = (t_monitor *)data;
	while (philos_need_to_eat(monitor->philos, monitor->num_philos)
		&& !someone_has_died(monitor->philos[0]->params))
	{
		index = 0;
		while (index < monitor->num_philos)
		{
			if (time_expired(monitor->philos, index))
			{
				pthread_mutex_lock(&(monitor->philos[0]->params->dead));
				monitor->philos[0]->params->one_dead = true;
				pthread_mutex_lock(&(monitor->philos[0]->params->print));
				printf("%lld %s%d died%s\n", get_timestamp(monitor->philos[index]->params->time),
				GREEN, index + 1, RESET);
				pthread_mutex_unlock(&(monitor->philos[0]->params->dead));
				pthread_mutex_unlock(&(monitor->philos[0]->params->print));
				break ;
			}
			index++;
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
// 	printf("Philo #%d of %d is a thread [%ld]\n\n", philo->index, (philo->params->num_philos), tid);
// 	return (NULL);
// }