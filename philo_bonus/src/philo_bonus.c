/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_bonus.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/21 15:38:31 by dloustal      #+#    #+#                 */
/*   Updated: 2025/08/01 16:24:09 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_param	*params;
	int		i;
	int		pid;

	params = init_params(argc, argv);
	if(!params)
		return (1);

	printf("Number of philos: %d\n", params->num_philos);
	i = 0;
	while (i < params->num_philos)
	{
		pid = fork();
		if (pid < 0)
			return (1);
		if (pid == 0)
		{
			//Child process
			// printf("Philo %d has been created\n", i);
			if (i % 2 == 1)
				usleep(200);
			sem_wait(params->forks);
			printf("%lld %s%d has taken a fork%s\n", get_timestamp(params->start), RED, i, RESET);
			sem_wait(params->forks);
			printf("%lld %s%d has taken a fork%s\n", get_timestamp(params->start), RED, i, RESET);
			printf("%lld %s%d is eating%s\n", get_timestamp(params->start), YELLOW, i, RESET);
			usleep(params->time_eat * 1000);
			sem_post(params->forks);
			sem_post(params->forks);
			printf("%lld %s%d is sleeping%s\n", get_timestamp(params->start), BLUE, i, RESET);
			usleep(params->time_sleep * 1000);
			printf("%lld %s%d is thinking%s\n", get_timestamp(params->start), GRAY, i, RESET);
			sem_close(params->forks);
			return (0);
		}
		else
		{
			// break ;
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