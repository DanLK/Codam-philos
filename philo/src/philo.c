/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/04 16:19:42 by dloustalot    #+#    #+#                 */
/*   Updated: 2025/07/22 11:54:01 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_data	*init_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	memset(data, 0, sizeof(t_data));
	return (data);
}

static t_data	*populate_data(int argc, char **argv)
{
	t_data		*data;
	t_param		*params;
	t_philo		**philos;
	t_fork		**forks;
	t_monitor	*monitor;

	data = init_data();
	if (!data)
		return (NULL);
	params = parse_params(argc, argv);
	if (!params)
		return (free(data), NULL);
	forks = init_forks(params);
	if (!forks)
		return (NULL);
	philos = init_philos(params, forks);
	if (!philos)
		return (clear_fork_arr(forks, params->num_philos),
			free(params), NULL);
	monitor = init_monitor(philos, params->num_philos);
	if (!monitor)
		return (clear_philo_data(params, philos, forks), NULL);
	data->params = params;
	data->philos = philos;
	return (data->forks = forks, data->monitor = monitor, data);
}

static void	clear_data(t_data *data)
{
	clear_fork_arr(data->forks, data->params->num_philos);
	clear_philo_arr(data->philos, data->params->num_philos);
	free(data->params);
	free(data->monitor);
	free(data);
}

int	main(int argc, char **argv)
{
	t_data		*data;
	int			i;

	i = -1;
	data = populate_data(argc, argv);
	if (!data)
		return (1);
	data->params->time = get_start_time() + 200;
	while (++i < data->params->num_philos)
		if (pthread_create(&data->philos[i]->tid, NULL, life_routine,
				data->philos[i]) != 0)
			return (clear_data(data), 1);
	if (pthread_create(&data->monitor->tid, NULL, monitor_routine,
			data->monitor) != 0)
		return (clear_data(data), 1);
	if (pthread_join(data->monitor->tid, NULL) != 0)
		return (clear_data(data), 1);
	i = 0;
	while (i < data->params->num_philos)
		if (pthread_join(data->philos[i++]->tid, NULL) != 0)
			return (clear_data(data), 1);
	destroy_mutexes(data->params, data->forks, data->philos);
	return (clear_data(data), 0);
}
