/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aestrell <aestrell@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 22:55:08 by aestrell          #+#    #+#             */
/*   Updated: 2024/08/06 22:55:08 by aestrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"


static char binary[9];
static int  it = 0;


char    binary_to_char(const char *binary)
{
    char    ch;
    int     i;

    i = 0;
    ch = 0;
    while (i < 8)
    {
        if (binary[i] == '1')
            ch += (1 << (7 - i));
        i++;
    }
    return ch;
}

void    signal_hanlder(int signal)
{
    if (signal == SIGUSR1)
        binary[it] = '1';
    else if (signal == SIGUSR2)
        binary[it] = '0';
    it++;
    if (it == 8)
    {
        binary[8] = '\0';

        char ch = binary_to_char(binary);
        if (binary[8] == '\0')
            ft_printf("\n");
        else
            ft_printf("%c", ch);
        it = 0;
    }
}

int main(void)
{
    struct sigaction    sa;
    pid_t               pid;

    sa.sa_sigaction = NULL;
    sa.sa_handler = signal_hanlder;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);

    pid = getpid();
    ft_printf("Sever PID: %d\n", pid);
    while (1)
        pause();
}
