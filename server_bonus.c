/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiacha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 17:59:08 by mchiacha          #+#    #+#             */
/*   Updated: 2025/11/25 17:59:14 by mchiacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE
#define _POSIX_C_SOURCE 200809L

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_state
{
    int             pidclient;
    int             receiving_pid;
    unsigned int    tmp_pid;
    int             pid_bits;

    char            *msg;
    size_t          len;

    unsigned char   byte;
    int             bitcount;

}   t_state;

static t_state g = {0, 1, 0, 0, NULL, 0, 0, 0};

void    add_byte(unsigned char b)
{
    char *new = malloc(g.len + 2);
    if (!new)
        return;
    for (size_t i = 0; i < g.len; i++)
        new[i] = g.msg[i];
    new[g.len] = b;
    new[g.len + 1] = '\0';
    free(g.msg);
    g.msg = new;
    g.len++;
}

void    reset_message(void)
{
    write(1, g.msg, g.len);
    write(1, "\n", 1);

    free(g.msg);
    g.msg = NULL;
    g.len = 0;

    g.receiving_pid = 1;
    g.tmp_pid = 0;
    g.pid_bits = 0;
    g.pidclient = 0;
}

void    handler(int sig, siginfo_t *info, void *ctx)
{
    (void)ctx;

    if (g.receiving_pid)
    {
        g.tmp_pid = (g.tmp_pid << 1) | (sig == SIGUSR1);
        g.pid_bits++;

        if (g.pid_bits == 32)
        {
            g.pidclient = g.tmp_pid;
            g.receiving_pid = 0;
            g.tmp_pid = 0;
            g.pid_bits = 0;
        }
    }
    else
    {
        g.byte = (g.byte << 1) | (sig == SIGUSR1);
        g.bitcount++;

        if (g.bitcount == 8)
        {
            if (g.byte == '\0')
                reset_message();
            else
                add_byte(g.byte);

            g.byte = 0;
            g.bitcount = 0;
        }
    }

    kill(info->si_pid, SIGUSR1); 
}

void    ft_putnbr(int n)
{
    if (n >= 10)
        ft_putnbr(n / 10);
    char c = '0' + (n % 10);
    write(1, &c, 1);
}

int main(void)
{
    struct sigaction sa;

    ft_putnbr(getpid());
    write(1, "\n", 1);

    sa.sa_sigaction = handler;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);

    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);

    while (1)
        pause();
}
