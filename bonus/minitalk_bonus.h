/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makkach <makkach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:31:26 by makkach           #+#    #+#             */
/*   Updated: 2025/03/08 14:41:36 by makkach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>

# define MAX_PID 99998

void	signal_handler_helper(unsigned char *buffer,
			pid_t client_pid, int expected_bytes, int bit_count);
void	kill_wrapper(int pid, int signal);

#endif
