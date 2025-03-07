/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makkach <makkach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:22:54 by makkach           #+#    #+#             */
/*   Updated: 2025/03/07 13:03:49 by makkach          ###   ########.fr       */
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
int	get_utf8_bytes(unsigned char first_byte)
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

void	reset_state(pid_t *client_pid, unsigned char *buffer, int *bit_count,
					int *byte_index, int *expected_bytes)
{
	*client_pid = 0;
	*bit_count = 0;
	*byte_index = 0;
	*expected_bytes = 1;
	buffer[0] = 0;
	buffer[1] = 0;
	buffer[2] = 0;
	buffer[3] = 0;
}

void	signal_handler(int signal, siginfo_t *info, void *context)
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
		reset_state(&client_pid, buffer, &bit_count, &byte_index, &expected_bytes);
	if (signal == SIGUSR1)
		buffer[byte_index] |= (1 << (bit_count % 8));
	bit_count++;
	if (bit_count % 8 == 0)
	{
		if (byte_index == 0)
			expected_bytes = get_utf8_bytes(buffer[0]);
		byte_index++;
		if (byte_index == expected_bytes)
		{
			if (buffer[0] == 0)
			{
				write(1, "\n", 1);
				kill(client_pid, SIGUSR1);
			}
			else
				write(1, buffer, expected_bytes);
			bit_count = 0;
			byte_index = 0;
			expected_bytes = 1;
			buffer[0] = 0;
			buffer[1] = 0;
			buffer[2] = 0;
			buffer[3] = 0;
		}
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

void	len_calcs(int *len, int *current_char, int bitecount)
{
	if (bitecount == 8)
	{
		if (current_char[0] >= 0 && current_char[0] <= 127)
			*len = 8;
		else if (current_char[0] >= 128 && current_char[0] <= 2047)
			*len = 16;
		else if (current_char[0] >= 2048 && current_char[0] <= 65535)
			*len = 24;
		else if (current_char[0] >= 65536 && current_char[0] <= 1114111)
			*len = 32;
	}
}

void	i_count(int *i, int len, int bitcount)
{
	if (bitcount == 0 && len == 8)
		*i = 0;
	else if (bitcount == 8 && len == 16)
		*i = 1;
	else if (bitcount == 16 && len == 24)
		*i = 2;
	else if (bitcount == 24 && len == 32)
		*i = 3;
}

// void	signal_handler(int signal, siginfo_t *info, void *context)
// {
// 	static int		current_char[4];
// 	static int		bit_count;
// 	static int		i;
// 	static pid_t	client_pid;
// 	static int		len;

// 	(void)context;
// 	if (client_pid == 0)
// 		client_pid = info->si_pid;
// 	if (client_pid != info->si_pid)
// 	{
// 		client_pid = 0;
// 		current_char[0] = 0;
// 		current_char[1] = 0;
// 		current_char[2] = 0;
// 		current_char[3] = 0;
// 		bit_count = 0;
// 	}
// 	if (signal == SIGUSR1)
// 		current_char[i] |= (1 << bit_count);
// 	bit_count++;
// 	len_calcs(&len, current_char, bit_count);
// 	i_count(&i, len, bit_count);
// 	if (bit_count == len)
// 	{
// 		if (current_char[0] == '\0')
// 			(write(1, "\0", 1), kill(client_pid, SIGUSR1));
// 		else
// 			(write(1, &current_char, 1));
// 		current_char[0] = 0;
// 		current_char[1] = 0;
// 		current_char[2] = 0;
// 		current_char[3] = 0;
// 		bit_count = 0;
// 		len = 8;
// 	}
// }