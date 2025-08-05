/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_bonus.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/21 15:38:31 by dloustal      #+#    #+#                 */
/*   Updated: 2025/08/05 17:01:31 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_param		*params;
	int			i;
	int			pid;
	// t_pids		*pids;
	t_philo		*philo;
	pthread_t	tmonitor_id;

	params = init_params(argc, argv);
	if (!params)
		return (1);
	philo = init_philo();
	if (!philo)
		return (1);
	printf("Number of philos: %d\n", params->num_philos);
	i = 0;
	while (i < params->num_philos)
	{
		pid = fork();
		pthread_create(&tmonitor_id, NULL, monitor_routine, params);
		pthread_join(tmonitor_id, NULL); // Chekc for errors
		if (pid < 0)
			return (1);
		if (pid == 0)
		{
			//Child process
			// printf("Philo %d has been created\n", i);
			if (i % 2 == 1)
				usleep(200);
			philo->times_eaten = 0;
			while (params->num_cycles == -1 || philo->times_eaten < params->num_cycles)
			{
				sem_wait(params->forks);
				printf("%lld %s%d has taken a fork%s\n", get_timestamp(params->start), RED, i, RESET);
				sem_wait(params->forks);
				printf("%lld %s%d has taken a fork%s\n", get_timestamp(params->start), RED, i, RESET);
				philo->last_meal = get_timestamp(params->start);
				printf("%lld %s%d is eating%s\n", get_timestamp(params->start), YELLOW, i, RESET);
				usleep(params->time_eat * 1000);
				philo->times_eaten++;
				sem_post(params->forks);
				sem_post(params->forks);
				
				printf("%lld %s%d is sleeping%s\n", get_timestamp(params->start), BLUE, i, RESET);
				usleep(params->time_sleep * 1000);
				printf("%lld %s%d is thinking%s\n", get_timestamp(params->start), GRAY, i, RESET);
			}
			sem_close(params->forks);
			return (0);
		}
		else
		{
			// break ;
			params->pids[i] = pid;
			printf("PID: %d\n", params->pids[i]);
		}
		i++;
	}
	i = 0;
	while (i < params->num_philos)
	{
		wait(NULL);
		i++;
	}


	


	return (0);
}

