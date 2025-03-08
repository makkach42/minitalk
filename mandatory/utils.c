/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makkach <makkach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:08:09 by makkach           #+#    #+#             */
/*   Updated: 2025/03/08 16:08:59 by makkach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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
