/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_bonus.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/21 15:20:19 by dloustal      #+#    #+#                 */
/*   Updated: 2025/07/30 16:56:15 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
#define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <semaphore.h>
# include <string.h>
# include <unistd.h>

# define YELLOW "\e[1;33m"
# define YELlOW_B "\e[1;43m"
# define PURPLE "\e[1;35m"
# define PURPLE_B "\e[1;45m"
# define RED "\e[1;31m"
# define BLUE "\e[1;34m"
# define GRAY "\e[1;37m"
# define GREEN "\e[1;32m"
# define RESET "\e[0m"

typedef struct s_param
{
	int				num_philos;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				time_think;
	int				num_cycles;
	long long		time;
	bool			one_dead;
	sem_t			*forks;
}		t_param;

int	ft_atoi(const char *nptr);
t_param	*init_params(int argc, char **argv);

#endif