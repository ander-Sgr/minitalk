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

void handle_sg(int signum)
{
    ft_printf("hello %d", signum);
}

int main(void)
{
    handle_sg(3);
}
