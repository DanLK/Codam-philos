/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/07 13:41:20 by dloustal      #+#    #+#                 */
/*   Updated: 2025/07/09 16:39:02 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_param	*parse_params(int argc, char **argv)
{
	t_param	*params;

	if (argc < 5 || argc > 6)
	{
		printf("Usage: <number_of_philos> <time_to_die> <time_to_eat> <time_to_sleep> [times_each_philo_must_eat]\n");
		return (NULL);
	}
	else
	{
		params = malloc(sizeof(t_param));
		if (!params)
			return (NULL);
		memset(params, 0, sizeof(t_param));
		params->num_philos = atoi(argv[1]);
		params->time_die = atoi(argv[2]);
		params->time_eat = atoi(argv[3]);
		params->time_sleep = atoi(argv[4]);
		params->time = get_start_time();
		pthread_mutex_init(&params->print, NULL);
		if (argc == 6)
		params->num_cycles = atoi(argv[5]);
		else
		params->num_cycles = -1;
	}
	return (params);
}

t_philo	*init_one_philo(t_param *params, t_fork **forks, int i)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	memset(philo, 0, sizeof(t_philo));
	philo->index = i;
	philo->times_eaten = 0;
	philo->last_meal = 0;
	philo->tid = 0;
	// philo->total_philos = params->num_philos;
	// philo->time_eat = params->time_eat;
	philo->params = params;
	// pthread_mutex_init(&(philo->mutex_fork), NULL);
	philo->forks = forks;
	return (philo);
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
	return(philos);
}

t_fork	*init_one_fork(int index)
{
	t_fork	*fork;

	fork = malloc(sizeof(t_fork));
	if (!fork)
		return (NULL);
	fork->index = index;
	pthread_mutex_init(&(fork->mutex_fork), NULL);
	return (fork);
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