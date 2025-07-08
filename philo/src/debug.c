/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debug.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/07 15:32:16 by dloustal      #+#    #+#                 */
/*   Updated: 2025/07/08 15:47:37 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_philos(t_philo **philos, t_param *params)
{
	int	i;

	if (!philos || !params)
		return ;
	i = 0;
	while (i < params->num_philos)
	{
		printf("Philo #%d:\nTimes eaten: %d\nThread id: %ld\n\n", philos[i]->index, philos[i]->times_eaten, philos[i]->tid);
		i++;
	}
}