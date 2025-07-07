/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/04 16:19:42 by dloustalot    #+#    #+#                 */
/*   Updated: 2025/07/07 16:20:37 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_param	*params;
	t_philo	**philos;
	int		i;

	params = parse_params(argc, argv);
	if (!params)
		return (1);
	i = 0;
	printf("Num philos: %d\n", params->num_philos);
	printf("Time to die: %d\n", params->time_die);
	printf("Time to eat: %d\n", params->time_eat);
	printf("Time to sleep: %d\n", params->time_sleep);
	printf("Num cycles: %d\n____________________________\n\n", params->num_cycles);
	philos = init_philos(params);
	if (!philos)
		return (free(params), 1);
	while (i < params->num_philos)
	{
		pthread_create(&philos[i]->tid, NULL, eat_routine, philos[i]);
		i++;
	}
	i = 0;
	while (i < params->num_philos)
	{
		pthread_join(philos[i]->tid, NULL);
		i++;
	}
	printf("--------------------------------------\n");
	// print_philos(philos, params);
	clear_philo_arr(philos, params->num_philos);
	free(params);
	return (0);
}
