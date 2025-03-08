/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makkach <makkach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:22:54 by makkach           #+#    #+#             */
/*   Updated: 2025/03/08 21:26:42 by makkach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_putnbr(int n)
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

static void	signal_handler(int signal, siginfo_t *info, void *v)
{
	static int	current_char;
	static int	bit_count;
	static int	client_pid;

	(void)v;
	if (client_pid == 0)
		client_pid = info->si_pid;
	if (client_pid != info->si_pid)
	{
		client_pid = 0;
		current_char = 0;
		bit_count = 0;
	}
	if (signal == SIGUSR1)
		current_char |= (1 << bit_count);
	bit_count++;
	if (bit_count == 8)
	{
		if (current_char >= 0 && current_char <= 127)
			write(1, &current_char, 1);
		current_char = 0;
		bit_count = 0;
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	(void)argv;
	if (argc != 1)
		return (0);
	ft_putnbr(getpid());
	write(1, "\n", 1);
	sa.sa_sigaction = signal_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset_wraper(&sa.sa_mask);
	sigaction_wraper(SIGUSR1, &sa, NULL);
	sigaction_wraper(SIGUSR2, &sa, NULL);
	while (42)
	{
		pause();
	}
}
