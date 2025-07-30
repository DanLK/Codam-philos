/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   atoi.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/07/17 19:00:42 by dloustal      #+#    #+#                 */
/*   Updated: 2025/07/30 12:58:58 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <stdbool.h>

static bool	is_space(char c)
{
	return (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v');
}

static bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static bool	is_sign(char c)
{
	return (c == '+' || c == '-');
}

int	ft_atoi(const char *nptr)
{
	int		nb;
	int		sign;
	char	*str;

	str = (char *)nptr;
	nb = 0;
	sign = 1;
	while (is_space(*str))
		str++;
	if (is_sign(*str))
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (is_digit(*str))
	{
		nb *= 10;
		nb += *str - '0';
		str++;
	}
	return (nb * sign);
}