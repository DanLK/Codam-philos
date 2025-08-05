/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/29 16:58:44 by dloustal      #+#    #+#                 */
/*   Updated: 2025/08/05 16:51:36 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	get_time_to_think(int eat, int sleep, int n)
{
	int	think;

	think = eat + (n % 2) * eat - sleep;
	if (think >= 0)
		return (think);
	else
		return (0);
}

t_param	*init_params(int argc, char **argv)
{
	t_param	*params;

	if (argc < 5 || argc > 6)
		return (printf("Usage: <N> <ms_die> <ms_eat> <ms_sleep> [meals]\n"),
			printf("Parameters should be positive integers\n"), NULL);
	params = malloc(sizeof(t_param));
	if (!params)
		return (params);
	memset(params, 0, sizeof(t_param));
	params->num_philos = ft_atoi(argv[1]);
	params->time_die = ft_atoi(argv[2]);
	params->time_eat = ft_atoi(argv[3]);
	params->time_sleep = ft_atoi(argv[4]);
	params->time_think = get_time_to_think(params->time_eat, params->time_sleep, params->num_philos);
	params->start = get_start_time();
	params->forks = sem_open("forks", O_CREAT, 0644, params->num_philos);// check for errors
	sem_unlink("forks");
	params->death_sem = sem_open("death", O_CREAT, 0644, 1);
	sem_unlink("death");
	params->pids = malloc((params->num_philos + 1) * sizeof(int));
	if (!params->pids)
		return (free(params), NULL);
	if (argc == 6)
		params->num_cycles = ft_atoi(argv[5]);
	else
		params->num_cycles = -1;
	return (params);
}

t_philo	*init_philo(void)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	memset(philo, 0, sizeof(t_philo));
	return (philo);
}

// t_pids	*init_pids(t_param *params)
// {
// 	t_pids	*pids_struct;
// 	pids_struct = malloc(sizeof(t_pids));
// 	if (!pids_struct)
// 		return (NULL);
// 	pids_struct->pids = malloc((params->num_philos + 1) * sizeof(int));
// 	if (!pids_struct->pids)
// 		return (free(pids_struct), NULL);
// 	return (pids_struct);
// }