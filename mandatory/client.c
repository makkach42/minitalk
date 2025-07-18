/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makkach <makkach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:23:02 by makkach           #+#    #+#             */
/*   Updated: 2025/03/12 17:16:23 by makkach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	ft_atoi(const char *str)
{
	int		sign;
	long	number;
	int		i;
	int		check;

	sign = 1;
	number = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		check = number;
		number = number * 10 + (str[i] - '0');
		if ((number / 10) != check)
			return (-1);
		i++;
	}
	return ((int)number * sign);
}

static void	sending_signal(char argv, int pid)
{
	int	j;

	j = 0;
	while (j < 8)
	{
		if (argv & 1 << j)
			kill_wrapper(pid, SIGUSR1);
		else
			kill_wrapper(pid, SIGUSR2);
		(j)++;
		usleep(500);
	}
}

static int	pid_check(char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (1);
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '\0')
		return (1);
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] != '\0')
		return (1);
	return (0);
}

int	main(int argc, char *argv[])
{
	int	pid;
	int	i;

	i = 0;
	if (argc != 3)
		return (write(2, "Error\n", 6), 1);
	if (pid_check(argv[1]) == 1)
		return (write(2, "Error\n", 6), 1);
	pid = ft_atoi(argv[1]);
	if (pid < 100 || pid > MAX_PID)
		return (write(2, "Error\n", 6), 1);
	while (argv[2][i])
	{
		sending_signal(argv[2][i], pid);
		i++;
	}
	sending_signal('\0', pid);
}
