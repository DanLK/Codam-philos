/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/07 13:41:20 by dloustal      #+#    #+#                 */
/*   Updated: 2025/07/18 14:45:55 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	get_time_to_think(int eat, int sleep, int n)
{
	int	think;

	think = eat + (n % 2) * eat - sleep;
	if (think >= 0)
		return (think);
	else
		return (0);
}

t_param	*parse_params(int argc, char **argv)
{
	t_param	*params;

	if (argc < 5 || argc > 6)
		return (printf("Usage: <N> <ms_die> <ms_eat> <ms_sleep> [meals]\n"),
			NULL);
	params = malloc(sizeof(t_param));
	if (!params)
		return (NULL);
	memset(params, 0, sizeof(t_param));
	params->num_philos = ft_atoi(argv[1]);
	params->time_die = ft_atoi(argv[2]);
	params->time_eat = ft_atoi(argv[3]);
	params->time_sleep = ft_atoi(argv[4]);
	params->time = 0;
	params->time_think = get_time_to_think(params->time_eat, params->time_sleep,
			params->num_philos);
	pthread_mutex_init(&params->time_mutex, NULL);
	pthread_mutex_init(&params->dead, NULL);
	pthread_mutex_init(&params->print, NULL);
	if (argc == 6)
		params->num_cycles = ft_atoi(argv[5]);
	else
		params->num_cycles = -1;
	return (params);
}

t_philo	**init_philos(t_param *params, t_fork **forks)
{
	t_philo	**philos;
	int		i;

	philos = malloc((params->num_philos + 1) * sizeof(t_philo *));
	if (!philos)
		return (NULL);
	i = 0;
	while (i < params->num_philos)
	{
		philos[i] = init_one_philo(params, forks, i);
		if (!philos[i])
			return (clear_philo_arr(philos, i), NULL);
		i++;
	}
	philos[i] = NULL;
	return (philos);
}

t_fork	**init_forks(t_param *params)
{
	t_fork	**forks;
	int		i;

	forks = malloc((params->num_philos + 1) * sizeof(t_fork *));
	if (!forks)
		return (NULL);
	i = 0;
	while (i < params->num_philos)
	{
		forks[i] = init_one_fork(i);
		if (!forks[i])
			return (clear_fork_arr(forks, i), NULL);
		i++;
	}
	forks[i] = NULL;
	return (forks);
}

t_monitor	*init_monitor(t_philo **philos, int num_philos)
{
	t_monitor	*monitor;

	if (!philos)
		return (NULL);
	monitor = malloc(sizeof(t_monitor));
	if (!monitor)
		return (NULL);
	memset(monitor, 0, sizeof(t_monitor));
	monitor->philos = philos;
	monitor->num_philos = num_philos;
	return (monitor);
}
