/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clear.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/07 15:03:47 by dloustal      #+#    #+#                 */
/*   Updated: 2025/07/07 15:24:51 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	clear_philo(t_philo *philo)
{
	free(philo);
}

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

