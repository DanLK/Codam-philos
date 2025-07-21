/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/21 14:25:14 by dloustal      #+#    #+#                 */
/*   Updated: 2025/07/21 14:27:44 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	someone_died(t_param *params)
{
	bool	someone_died;
	
	pthread_mutex_lock(&(params->dead));
	someone_died = params->one_dead;
	pthread_mutex_unlock(&(params->dead));
	return (someone_died);
}

bool	inevitable_death(t_param *params)
{
	bool	dead;

	dead = false;
	while (!dead)
	{
		pthread_mutex_lock(&(params->dead));
		dead = params->one_dead;
		pthread_mutex_unlock(&(params->dead));
		if (!dead)
			usleep(500);
		else
			return (true);
	}
	return (false);
}