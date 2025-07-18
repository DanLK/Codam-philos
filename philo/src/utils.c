/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/09 11:59:31 by dloustal      #+#    #+#                 */
/*   Updated: 2025/07/18 14:54:44 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_start_time(void)
{
	struct timeval	current_time;
	int				code;
	long long		start_time;

	code = gettimeofday(&current_time, NULL);
	if (code != 0)
		return (0);
	start_time = (long long)current_time.tv_sec * 1000
		+ (current_time.tv_usec / 1000);
	return (start_time);
}

long long	get_timestamp(long long start_time)
{
	struct timeval	current_time;
	int				code;
	long long		time;

	code = gettimeofday(&current_time, NULL);
	if (code != 0)
		return (0);
	time = ((long long)current_time.tv_sec * 1000
			+ (current_time.tv_usec / 1000)) - start_time;
	return (time);
}
