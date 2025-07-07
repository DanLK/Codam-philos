/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routines.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/07 15:43:39 by dloustal      #+#    #+#                 */
/*   Updated: 2025/07/07 16:41:54 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*simple_routine(void *data)
{
	pthread_t	tid;
	t_philo		*philo;

	philo = (t_philo *)data;
	tid = pthread_self();
	printf("Philo #%d is a thread [%ld]\n\n", philo->index, tid);
	return (NULL);
}

void	*eat_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	pthread_mutex_lock(&(philo->mutex_fork));
	printf("Philo #%d has grabbed their left (own) fork\n", philo->index);
	printf("Philo #%d is trying to get their right neighbor #%d's fork\n", philo->index, (philo->index + 1) % philo->total_philos );
	// printf("%d\n", (int)(philo->time_eat));
	usleep(philo->time_eat * 1000);
	pthread_mutex_unlock(&(philo->mutex_fork));
	printf("Philo #%d has released their left (own) fork\n", philo->index);
	return (NULL);
}