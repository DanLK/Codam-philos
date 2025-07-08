/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clear.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/07 15:03:47 by dloustal      #+#    #+#                 */
/*   Updated: 2025/07/08 14:18:31 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	clear_philo(t_philo *philo)
{
	free(philo); //Need to free the other pointers as well
}

static void	clear_fork(t_fork *fork)
{
	// free((fork->mutex_fork));
	free(fork);
}

//Can make this function generic by passing as a parameter a function pointer 
void	clear_philo_arr(t_philo **philos, int index)
{
	int	i;

	i = 0;
	while (philos[i] && i < index)
	{
		clear_philo(philos[i]);
		i++;
	}
	free(philos);
}

void	clear_fork_arr(t_fork **forks, int index)
{
	int	i;

	i = 0;
	while (forks[i] && i < index)
	{
		clear_fork(forks[i]);
		i++;
	}
	free(forks);
}

