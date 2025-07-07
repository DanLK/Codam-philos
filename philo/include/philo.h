/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/04 16:50:26 by dloustalot    #+#    #+#                 */
/*   Updated: 2025/07/07 13:43:54 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>

typedef struct s_param
{
	int	num_philos;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	num_cycles;
}		t_param;

//Init
t_param	*parse_params(int argc, char **argv);

#endif