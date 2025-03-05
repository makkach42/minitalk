/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makkach <makkach@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:23:02 by makkach           #+#    #+#             */
/*   Updated: 2025/03/05 13:10:35 by makkach          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int main(int argc, char const *argv[])
{
    int pid;
    int i;
    int j;

    if (argc != 3)
    {
        write(1, "Error\n", 6);
        return (0);
    }
    pid = ft_atoi(argv[1]);
    i = 0;
    while (argv[2][i])
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
        i++;
    }
    j = 0;
    while (j < 8)
    {
        kill(pid, SIGUSR2);
        j++;
        usleep(100);
    }
    return 0;
}
