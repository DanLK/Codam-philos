/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/04 16:19:42 by dloustalot    #+#    #+#                 */
/*   Updated: 2025/07/07 13:45:42 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_param	*params;

	params = parse_params(argc, argv);
	if (!params)
		return (1);
	printf("Num philos: %d\n", params->num_philos);
	printf("Time to die: %d\n", params->time_die);
	printf("Time to eat: %d\n", params->time_eat);
	printf("Time to sleep: %d\n", params->time_sleep);
	printf("Num cycles: %d\n", params->num_cycles);
	free(params);
	return (0);
}