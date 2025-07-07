/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routines.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/07 15:43:39 by dloustal      #+#    #+#                 */
/*   Updated: 2025/07/07 15:55:14 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*simple_routine(void *data)
{
	// int			index;
	pthread_t	tid;
	t_philo		*philo;

	philo = (t_philo *)data;
	tid = pthread_self();
	printf("Philo #%d is a thread [%ld]\n\n", philo->index, tid);
	return (NULL);
}