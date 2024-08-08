/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aestrell <aestrell@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 23:27:46 by aestrell          #+#    #+#             */
/*   Updated: 2024/08/06 23:27:46 by aestrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void    sendBinary(pid_t pid, const char *binary)
{
    int i;

    i = 0;
    while (i < 8)
    {
        if (binary[i] == '1')
        {
            if (kill(pid, SIGUSR1) == -1)
            {
                ft_printf("Error sending SIGUSR1\n");
                exit(EXIT_FAILURE);
            }
        }
         else
        {
            if(kill(pid, SIGUSR2) == -1)
            {
                ft_printf("Error sending SIGUSR2\n");
                exit(EXIT_FAILURE);
            }
        }
            usleep(100);
        i++;
    }
}

void    char_to_bin(char ch, char *binary)
{
    int i;

    i = 7;
    while (i >= 0)
    {
        binary[7 - i] = (ch & (1 << i)) ? '1' : '0';
        i--;
    }
    binary[8] = '\0';
}

int main(int argc, char *argv[])
{
    pid_t   pid;
    char    *message;
    size_t  i;
    char    binary[9];

    if (argc != 3)
    {
        ft_printf("Usage: %s <PID> <string>\n", argv[0]);
    }

    i = 0;
    message = argv[2];
    pid = ft_atoi(argv[1]);
    ft_printf("Sending message '%s' to PID %d\n", message, pid);
    while (i < ft_strlen(message))
    {
        char_to_bin(message[i], binary);
        sendBinary(pid, binary);
        i++;
    }
}
