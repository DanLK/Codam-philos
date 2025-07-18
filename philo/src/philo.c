/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/04 16:19:42 by dloustalot    #+#    #+#                 */
/*   Updated: 2025/07/18 13:53:56 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_param		*params;
	t_philo		**philos;
	t_fork		**forks;
	t_monitor	*monitor;
	int			i;

	params = parse_params(argc, argv);
	if (!params)
		return (1);
	i = 0;
	forks = init_forks(params);
	if (!forks)
		return (free(params), 1);
	philos = init_philos(params, forks);
	if (!philos)
		return (clear_fork_arr(forks, params->num_philos), free(params), 1);
	monitor = init_monitor(philos, params->num_philos);
	if (!monitor)
		return (clear_philo_data(params, philos, forks), 1);
	params->time = get_start_time() + 50;
	while (i < params->num_philos)
	{ 
		if (pthread_create(&philos[i]->tid, NULL, life_routine, philos[i]) != 0)
			return (free(monitor), clear_philo_data(params, philos, forks), 1);
		i++;
	}
	if (pthread_create(&monitor->tid, NULL, monitor_routine, monitor) != 0)
		return (free(monitor), clear_philo_data(params, philos, forks), 1);
	if (pthread_join(monitor->tid, NULL) != 0)
		return (free(monitor), clear_philo_data(params, philos, forks), 1);
	i = 0;
	while (i < params->num_philos)
	{
		if (pthread_join(philos[i]->tid, NULL) != 0)
			return (free(monitor), clear_philo_data(params, philos, forks), 1);
		i++;
	}
	destroy_mutexes(params, forks, philos);
	free(monitor);
	clear_philo_data(params, philos, forks);
	return (0);
}
