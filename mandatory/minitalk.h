/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makkach <makkach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:31:26 by makkach           #+#    #+#             */
/*   Updated: 2025/03/08 21:27:22 by makkach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>

# define MAX_PID 99998

void	kill_wrapper(int pid, int signal);
void	sigaction_wraper(int sig, void *act, void *oldact);
void	sigemptyset_wraper(sigset_t *sa_mask);

#endif
