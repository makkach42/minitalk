/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makkach <makkach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:23:02 by makkach           #+#    #+#             */
/*   Updated: 2025/03/05 14:15:13 by makkach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int main(int argc, char const *argv[])
{
    int pid;
    int i;
    int j;

    if (argc != 3) 
        return (write(2, "Error\n", 6), 0);
    pid = ft_atoi(argv[1]);
    if (pid < 100 || pid > 99998)
        return (write(2, "Error\n", 6), 0);
    i = -1;
    while (argv[2][++i])
    {
        j = 0;
        while (j < 8)
        {
            if (argv[2][i] & 1 << j)
                kill(pid, SIGUSR1);
            else
                kill(pid, SIGUSR2);
            j++;
            usleep(100);
        }
    }
    j = 0;
    while (j < 8)
    {
        kill(pid, SIGUSR2);
        j++;
        usleep(100);
    }
}
