/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routines.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/07 15:43:39 by dloustal      #+#    #+#                 */
/*   Updated: 2025/07/17 16:24:49 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*simple_routine(void *data)
{
	pthread_t	tid;
	t_philo		*philo;

	philo = (t_philo *)data;
	tid = pthread_self();
	printf("Philo #%d of %d is a thread [%ld]\n\n", philo->index, (philo->params->num_philos), tid);
	return (NULL);
}

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
	printf("%lld %s%d has taken a fork%s\n", get_timestamp(philo->params->time), YELLOW, philo->index, RESET);
	pthread_mutex_unlock(&(philo->params->print));
	if (philo->index == i_neighbor)
		return (pthread_mutex_unlock(&(philo->forks[first]->mutex_fork)), NULL);
	pthread_mutex_lock(&(philo->forks[second]->mutex_fork));
	if (someone_has_died(philo->params))
		return (pthread_mutex_unlock(&(philo->forks[first]->mutex_fork)),
			pthread_mutex_unlock(&(philo->forks[second]->mutex_fork)), NULL);
	pthread_mutex_lock(&(philo->params->print));
	printf("%lld %s%d has taken a fork%s\n", get_timestamp(philo->params->time), YELLOW, philo->index, RESET);
	pthread_mutex_unlock(&(philo->params->print));
	pthread_mutex_lock(&(philo->last_meal_mut));
	if (someone_has_died(philo->params))
		return (pthread_mutex_unlock(&(philo->last_meal_mut)), NULL);
	philo->last_meal = get_timestamp(philo->params->time);
	pthread_mutex_lock(&(philo->params->print));
	printf("%lld %s%d is eating%s\n", philo->last_meal, RED, philo->index, RESET);
	pthread_mutex_unlock(&(philo->last_meal_mut));
	pthread_mutex_unlock(&(philo->params->print));
	usleep(philo->params->time_eat * 1000);
	pthread_mutex_lock(&(philo->x_eaten_mut));
	philo->times_eaten++;
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
	// long long	start;

	philo = (t_philo *)data;
	while (get_start_time() < philo->params->time)
		usleep(30);
	// printf("%lld %d starting to live\n", get_timestamp(philo->params->time), philo->index);
	if (philo->index % 2 == 1)
		usleep(1000);
	while (!completed_meals(philo))
	{
		// if (someone_has_died(philo->params))
		// 	break ;
		eat_routine(data);
		// if (someone_has_died(philo->params))
		// 	break ;
		if (completed_meals(philo))
			break ;
		sleep_routine(data);
		if (someone_has_died(philo->params))
			break ;
		pthread_mutex_lock(&(philo->params->print));
		printf("%lld %s%d is thinking%s\n", get_timestamp(philo->params->time), GRAY, philo->index, RESET);
		pthread_mutex_unlock(&(philo->params->print));
		usleep(philo->params->time_think);
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
	printf("%lld %s%d is sleeping%s\n", get_timestamp(philo->params->time), BLUE, index, RESET);
	pthread_mutex_unlock(&(philo->params->print));
	usleep(philo->params->time_sleep * 1000);
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
				GREEN, index, RESET);
				pthread_mutex_unlock(&(monitor->philos[0]->params->dead));
				pthread_mutex_unlock(&(monitor->philos[0]->params->print));
				break ;
			}
			index++;
		}
	}
	return (NULL);
}


void	*eat_routine_old(void *data)
{
	t_philo		*philo;
	int			index;
	int			i_neighbor;
	// long long	last_meal;

	philo = (t_philo *)data;
	index = philo->index;
	i_neighbor = (index + 1) % philo->params->num_philos;
	if (index == philo->params->num_philos -1)
		pthread_mutex_lock(&(philo->forks[0]->mutex_fork));
	else
		pthread_mutex_lock(&(philo->forks[index]->mutex_fork));
	if (someone_has_died(philo->params))
		return (NULL);
	pthread_mutex_lock(&(philo->params->print));
	// printf("%lld %sPhilo #%d has grabbed their left (own) fork%s\n", get_timestamp(philo->params->time), YELLOW, philo->index, RESET);
	printf("%lld %s%d has taken a fork%s\n", get_timestamp(philo->params->time), YELLOW, philo->index, RESET);
	// printf("Philo #%d is trying to get their right neighbor #%d's fork\n", philo->index, i_neighbor);
	pthread_mutex_unlock(&(philo->params->print));
	if (index == i_neighbor)
	{
		pthread_mutex_unlock(&(philo->forks[0]->mutex_fork));
		return (NULL);
	}
	if (index == philo->params->num_philos -1)
		pthread_mutex_lock(&(philo->forks[index]->mutex_fork));
	else
		pthread_mutex_lock(&(philo->forks[i_neighbor]->mutex_fork));
	if (someone_has_died(philo->params))
		return (NULL);
	pthread_mutex_lock(&(philo->params->print));
	// printf("[%lld] %sPhilo #%d has grabbed their neighbour's (#%d) fork%s\n", get_timestamp(philo->params->time), PURPLE, philo->index, i_neighbor, RESET);
	printf("%lld %s%d has taken a fork%s\n", get_timestamp(philo->params->time), YELLOW, philo->index, RESET);
	pthread_mutex_unlock(&(philo->params->print));
	philo->last_meal = get_timestamp(philo->params->time);
	// philo->last_meal = last_meal;
	pthread_mutex_lock(&(philo->params->print));
	printf("%lld %s%d is eating%s\n", philo->last_meal, RED, index, RESET);
	pthread_mutex_unlock(&(philo->params->print));
	usleep(philo->params->time_eat * 1000);
	philo->times_eaten++; //PROTECT WITH A MUTEX FOR THE MONITORING
	pthread_mutex_unlock(&((philo->forks[i_neighbor])->mutex_fork));
	// printf("%sPhilo #%d has released their neighbours's fork%s\n", PURPLE_B, philo->index, RESET);
	pthread_mutex_unlock(&((philo->forks[index])->mutex_fork));
	// printf("%sPhilo #%d has released their left (own) fork%s\n", YELlOW_B, philo->index, RESET);
	return (NULL);
}