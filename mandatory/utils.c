/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makkach <makkach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:19:26 by makkach           #+#    #+#             */
/*   Updated: 2025/03/05 14:03:14 by makkach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	check(int sign)
{
	if (sign > 0)
		return (-33);
	else
		return (-33);
}

int	ft_atoi(const char *str)
{
	int		sign;
	long	number;
	int		i;

	sign = 1;
	number = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (number > (((99998) - (str[i] - '0')) / 10))
			return (check(sign));
		number = number * 10 + (str[i] - '0');
		i++;
	}
	return ((int)number * sign);
}
