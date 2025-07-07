/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/07 13:41:20 by dloustal      #+#    #+#                 */
/*   Updated: 2025/07/07 15:50:17 by dloustal      ########   odam.nl         */
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
		if (argc == 6)
		params->num_cycles = atoi(argv[5]);
		else
		params->num_cycles = -1;
	}
	return (params);
}

t_philo	*init_one_philo(t_param *params, int i)
{
	t_philo	*philo;

	(void)params;
	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->index = i + 1;
	philo->times_eaten = 0;
	philo->tid = 0;
	return (philo);
}

t_philo	**init_philos(t_param *params)
{
	t_philo	**philos;
	int		i;

	philos = malloc((params->num_philos + 1) * sizeof(t_philo *));
	if (!philos)
		return (NULL);
	i = 0;
	while (i < params->num_philos)
	{
		philos[i] = init_one_philo(params, i);
		if (!philos[i])
			return (clear_philo_arr(philos, i), NULL);
		i++;
	}
	philos[i] = NULL;
	return(philos);
}
