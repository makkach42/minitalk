/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makkach <makkach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:22:54 by makkach           #+#    #+#             */
/*   Updated: 2025/03/08 14:54:27 by makkach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

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

static int	get_utf8_bytes(unsigned char first_byte)
{
	if ((first_byte & 0x80) == 0)
		return (1);
	else if ((first_byte & 0xE0) == 0xC0)
		return (2);
	else if ((first_byte & 0xF0) == 0xE0)
		return (3);
	else if ((first_byte & 0xF8) == 0xF0)
		return (4);
	return (1);
}

static void	reset_state(pid_t *client_pid, unsigned char *buffer,
			int *bit_count, int *byte_index)
{
	*client_pid = 0;
	*bit_count = 0;
	*byte_index = 0;
	buffer[0] = 0;
	buffer[1] = 0;
	buffer[2] = 0;
	buffer[3] = 0;
}

static void	signal_handler(int signal, siginfo_t *info, void *context)
{
	static unsigned char	buffer[4];
	static int				bit_count;
	static int				byte_index;
	static pid_t			client_pid;
	static int				expected_bytes;

	(void)context;
	if (client_pid == 0)
		client_pid = info->si_pid;
	if (client_pid != info->si_pid)
		(reset_state(&client_pid, buffer, &bit_count,
				&byte_index), expected_bytes = 0);
	if (signal == SIGUSR1)
		buffer[byte_index] |= (1 << (bit_count % 8));
	bit_count++;
	if (bit_count % 8 == 0)
	{
		if (byte_index == 0)
			expected_bytes = get_utf8_bytes(buffer[0]);
		byte_index++;
		if (byte_index == expected_bytes)
			(signal_handler_helper(buffer, client_pid,
					expected_bytes, bit_count), byte_index = 0);
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
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (42)
	{
		pause();
	}
}
