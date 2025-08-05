/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routines.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/05 15:57:37 by dloustal      #+#    #+#                 */
/*   Updated: 2025/08/05 16:58:02 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitor_routine(void *data)
{
	t_param	*params;

	params = (t_param *)data;
	sem_wait(params->death_sem);
	if (params->one_dead)
		printf("%s Someone has died%s\n", GREEN, RESET);
	sem_post(params->death_sem);
	return (NULL);
}