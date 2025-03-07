/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makkach <makkach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:22:22 by makkach           #+#    #+#             */
/*   Updated: 2025/03/07 13:33:27 by makkach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	signal_handler_helper(unsigned char *buffer, pid_t client_pid,
		int expected_bytes, int bit_count)
{
	if (buffer[0] == 0)
	{
		write(1, "\n", 1);
		kill(client_pid, SIGUSR1);
	}
	else
		write(1, buffer, expected_bytes);
	bit_count = 0;
	expected_bytes = 1;
	buffer[0] = 0;
	buffer[1] = 0;
	buffer[2] = 0;
	buffer[3] = 0;
}
