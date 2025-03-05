/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makkach <makkach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:22:54 by makkach           #+#    #+#             */
/*   Updated: 2025/03/05 16:16:00 by makkach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	ft_putnbr(int n)
{
	char	c;

	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
	}
	if (n > 9)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else
	{
		c = (n + '0');
		write(1, &c, 1);
	}
}

void	signal_handler(int signal, siginfo_t *info, void *context)
{
	static int		current_char;
	static int		bit_count;
	static pid_t	client_pid;

	(void)context;
	if (client_pid == 0 || client_pid != info->si_pid)
	{
		client_pid = info->si_pid;
		current_char = 0;
		bit_count = 0;
	}
	if (signal == SIGUSR1)
		current_char |= (1 << bit_count);
	bit_count++;
	if (bit_count == 8)
	{
		if (current_char == '\0')
			(write(1, "\n", 1), kill(client_pid, SIGUSR1));
		else
			(write(1, &current_char, 1), kill(client_pid, SIGUSR2));
		current_char = 0;
		bit_count = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	ft_putnbr(getpid());
	write(1, "\n", 1);
	sa.sa_sigaction = signal_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (42)
	{
		pause();
	}
}
