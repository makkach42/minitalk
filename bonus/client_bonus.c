/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makkach <makkach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:23:02 by makkach           #+#    #+#             */
/*   Updated: 2025/03/05 16:08:34 by makkach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static int	check(int sign)
{
	if (sign > 0)
		return (-33);
	else
		return (-33);
}

static int	ft_atoi(const char *str)
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
		if (number > (((9223372036854775807) - (str[i] - '0')) / 10))
			return (check(sign));
		number = number * 10 + (str[i] - '0');
		i++;
	}
	return ((int)number * sign);
}

static void	sending_signal(const char **argv, int *i, int *j, int *pid)
{
	while (argv[2][(*i)])
	{
		*j = 0;
		while (*j < 8)
		{
			if (argv[2][*i] & (1 << *j))
				kill(*pid, SIGUSR1);
			else
				kill(*pid, SIGUSR2);
			(*j)++;
			usleep(1000);
		}
		(*i)++;
	}
	*j = 0;
	while (*j < 8)
	{
		kill(*pid, SIGUSR2);
		usleep(1000);
		(*j)++;
	}
}
void	signal_handler(int signal)
{
	if (signal == SIGUSR2)
		write(1, ".", 1);
	else if (signal == SIGUSR1)
	{
		write(1, "\nComplete\n", 10);
		exit(0);
	}

}

int	main(int argc, char const *argv[])
{
	int	pid;
	int	i;
	int	j;

	if (argc != 3)
		return (write(2, "Error\n", 6), 0);
	pid = ft_atoi(argv[1]);
	if (pid < 100 || pid > MAX_PID)
		return (write(2, "Error\n", 6), 0);
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	i = 0;
	sending_signal(argv, &i, &j, &pid);
}
