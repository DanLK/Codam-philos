/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routines.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/07 15:43:39 by dloustal      #+#    #+#                 */
/*   Updated: 2025/07/11 15:57:50 by dloustal      ########   odam.nl         */
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

void	*eat_routine(void *data)
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
	pthread_mutex_lock(&(philo->params->print));
	// printf("%lld %sPhilo #%d has grabbed their left (own) fork%s\n", get_timestamp(philo->params->time), YELLOW, philo->index, RESET);
	printf("%lld %s%d has taken a fork%s\n", get_timestamp(philo->params->time), YELLOW, philo->index, RESET);
	// printf("Philo #%d is trying to get their right neighbor #%d's fork\n", philo->index, i_neighbor);
	pthread_mutex_unlock(&(philo->params->print));
	if (index == philo->params->num_philos -1)
		pthread_mutex_lock(&(philo->forks[index]->mutex_fork));
	else
		pthread_mutex_lock(&(philo->forks[i_neighbor]->mutex_fork));
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

void	*simple_combined_routine(void *data)
{
	t_philo	*philo;
	// int		think_time;

	philo = (t_philo *)data;
	// if (philo->params->num_cycles > 0)
	// {
	// if (philo->index % 2 != 0)
	// 	usleep(10);
	// think_time = (2 * philo->params->time_eat - philo->params->time_sleep) * 1000;
	while (philo->params->num_cycles == -1 || philo->times_eaten < philo->params->num_cycles)
	{
		// pthread_mutex_lock(&(philo->params->print));
		// pthread_mutex_unlock(&(philo->params->print));
		eat_routine(data);
		// printf("%lld %d has eaten %d times\n", get_timestamp(philo->params->time), philo->index, philo->times_eaten);
		sleep_routine(data);
		pthread_mutex_lock(&(philo->params->print));
		printf("%lld %s%d is thinking%s\n", get_timestamp(philo->params->time), GRAY, philo->index, RESET);
		pthread_mutex_unlock(&(philo->params->print));
		usleep(philo->params->time_think);
	}
	// }
	// else
	// {
	// 	eat_routine(data);
	// 	sleep_routine(data);
	// }
	return (NULL);
}

void	*sleep_routine(void *data)
{
	t_philo	*philo;
	int		index;

	philo = (t_philo *)data;
	index = philo->index;
	pthread_mutex_lock(&(philo->params->print));
	printf("%lld %s%d is sleeping%s\n", get_timestamp(philo->params->time), BLUE, index, RESET);
	pthread_mutex_unlock(&(philo->params->print));
	usleep(philo->params->time_sleep * 1000);
	pthread_mutex_lock(&(philo->params->print));
	// printf("[%lld] Philo %s#%d finished sleeping%s\n", get_timestamp(philo->params->time), BLUE, index, RESET);
	pthread_mutex_unlock(&(philo->params->print));
	return (NULL);
}

// void	*think_routine(void *data)
// {

// }
