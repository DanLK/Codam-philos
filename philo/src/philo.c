/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/04 16:19:42 by dloustalot    #+#    #+#                 */
/*   Updated: 2025/07/17 13:52:03 by dloustal      ########   odam.nl         */
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
		return (clear_fork_arr(forks, params->num_philos), clear_fork_arr(forks, params->num_philos), free(params), 1);
	pthread_create(&monitor->tid, NULL, monitor_routine, monitor);
	while (i < params->num_philos)
	{ 
		pthread_create(&philos[i]->tid, NULL, life_routine, philos[i]);
		i++;
	}
	i = 0;
	pthread_join(monitor->tid, NULL);
	while (i < params->num_philos)
	{
		pthread_join(philos[i]->tid, NULL);
		i++;
	}
	printf("--------------------------------------\n");
	// print_philos(philos, params);
	free(monitor);
	clear_fork_arr(forks, params->num_philos);
	clear_philo_arr(philos, params->num_philos);
	free(params);
	return (0);
}
