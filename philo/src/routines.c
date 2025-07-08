/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routines.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/07 15:43:39 by dloustal      #+#    #+#                 */
/*   Updated: 2025/07/08 15:30:38 by dloustal      ########   odam.nl         */
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
	t_philo	*philo;
	int		index;
	int		i_neighbor;

	philo = (t_philo *)data;
	index = philo->index;
	i_neighbor = (index + 1) % philo->params->num_philos;
	pthread_mutex_lock(&(philo->forks[index]->mutex_fork));
	printf("%sPhilo #%d has grabbed their left (own) fork%s\n", YELLOW, philo->index, RESET);
	printf("Philo #%d is trying to get their right neighbor #%d's fork\n", philo->index, i_neighbor);
	pthread_mutex_lock(&(philo->forks[i_neighbor]->mutex_fork));
	printf("%sPhilo #%d has grabbed their neighbour's (#%d) fork%s\n", PURPLE, philo->index, i_neighbor, RESET);
	// printf("%d\n", (int)(philo->params->time_eat));
	printf("Philo %s#%d is eating%s\n", RED, index, RESET);
	usleep(philo->params->time_eat * 1000);
	pthread_mutex_unlock(&((philo->forks[i_neighbor])->mutex_fork));
	printf("%sPhilo #%d has released their neighbours's fork%s\n", PURPLE_B, philo->index, RESET);
	pthread_mutex_unlock(&((philo->forks[index])->mutex_fork));
	printf("%sPhilo #%d has released their left (own) fork%s\n", YELlOW_B, philo->index, RESET);
	return (NULL);
}
