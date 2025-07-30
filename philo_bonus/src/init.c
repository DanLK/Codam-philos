/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/29 16:58:44 by dloustal      #+#    #+#                 */
/*   Updated: 2025/07/30 17:07:30 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	params->start = get_start_time();
	if (argc == 6)
		params->num_cycles = ft_atoi(argv[5]);
	else
		params->num_cycles = -1;
	return (params);
}
