/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makkach <makkach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 13:50:15 by makkach           #+#    #+#             */
/*   Updated: 2025/03/09 13:50:42 by makkach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	sigaddset_wraper(sigset_t *sa_mask, int sig)
{
	if (sigaddset(sa_mask, sig) == -1)
		exit(1);
}
