/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makkach <makkach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:22:22 by makkach           #+#    #+#             */
/*   Updated: 2025/03/09 13:39:11 by makkach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	signal_handler_helper(unsigned char *buffer, pid_t client_pid,
		int expected_bytes, int bit_count)
{
	if (buffer[0] == 0)
		kill_wrapper(client_pid, SIGUSR1);
	else
		write(1, buffer, expected_bytes);
	bit_count = 0;
	expected_bytes = 0;
	buffer[0] = 0;
	buffer[1] = 0;
	buffer[2] = 0;
	buffer[3] = 0;
}

void	kill_wrapper(int pid, int signal)
{
	if (kill(pid, signal) == -1)
		exit(1);
}

void	sigaction_wraper(int sig, void *act, void *oldact)
{
	if (sigaction(sig, act, oldact) == -1)
		exit(1);
}

void	signal_wraper(int sig, void *act)
{
	if (signal(sig, act) == SIG_ERR)
		exit(1);
}

void	sigemptyset_wraper(sigset_t *sa_mask)
{
	if (sigemptyset(sa_mask) == -1)
		exit(1);
}
