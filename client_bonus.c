/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiacha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 17:58:58 by mchiacha          #+#    #+#             */
/*   Updated: 2025/11/25 17:59:02 by mchiacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

volatile int g_ack = 0;

void ack_handler(int sig)
{
    (void)sig;
    g_ack = 1;
}

void send_bit(int pid, int bit)
{
    kill(pid, bit ? SIGUSR1 : SIGUSR2);
    while (!g_ack)
        usleep(10);
    g_ack = 0;
}

void send_int(int pid, unsigned int n)
{
    for (int i = 31; i >= 0; i--)
        send_bit(pid, (n >> i) & 1);
}

void send_char(int pid, unsigned char c)
{
    for (int i = 7; i >= 0; i--)
        send_bit(pid, (c >> i) & 1);
}

int ft_atoi(const char *s)
{
    long n = 0;
    while (*s >= '0' && *s <= '9')
        n = n * 10 + (*s++ - '0');
    return (int)n;
}

int main(int argc, char **argv)
{
    if (argc != 3)
        return (1);

    signal(SIGUSR1, ack_handler);

    int pid = ft_atoi(argv[1]);

    send_int(pid, getpid());

    for (int i = 0; argv[2][i]; i++)
        send_char(pid, argv[2][i]);

    send_char(pid, '\0');

    return (0);
}
