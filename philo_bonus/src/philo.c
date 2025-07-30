/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/21 15:38:31 by dloustal      #+#    #+#                 */
/*   Updated: 2025/07/30 13:10:44 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_param	*params;

	params = init_params(argc, argv);
	if(!params)
		return (1);

	printf("Number of philos: %d\n", params->num_philos);

	return (0);
}