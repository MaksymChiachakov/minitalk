/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiacha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 13:36:18 by mchiacha          #+#    #+#             */
/*   Updated: 2025/11/27 17:41:01 by mchiacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Libft/libft.h"
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_state
{
	int				pidclient;
	int				receiving_pid;
	unsigned int	tmp_pid;
	int				pid_bits;
	char			*msg;
	size_t			len;
	unsigned char	byte;
	int				bitcount;
}	t_state;

static t_state	g_g = {0, 1, 0, 0, NULL, 0, 0, 0};

void	add_byte(unsigned char b)
{
	char	*new;
	size_t	i;

	i = 0;
	new = malloc(g_g.len + 2);
	if (!new)
		return ;
	while (i < g_g.len)
	{
		new[i] = g_g.msg[i];
		i++;
	}
	new[g_g.len] = b;
	new[g_g.len + 1] = '\0';
	free(g_g.msg);
	g_g.msg = new;
	g_g.len++;
}

void	reset_message(void)
{
	write(1, g_g.msg, g_g.len);
	write(1, "\n", 1);
	free(g_g.msg);
	g_g.msg = NULL;
	g_g.len = 0;
	g_g.receiving_pid = 1;
	g_g.tmp_pid = 0;
	g_g.pid_bits = 0;
	g_g.pidclient = 0;
}

void	me(void)
{
	if (g_g.byte == '\0')
		reset_message();
	else
		add_byte(g_g.byte);
	g_g.byte = 0;
	g_g.bitcount = 0;
}

void	handler(int sig, siginfo_t *info, void *ctx)
{
	(void)ctx;
	if (g_g.receiving_pid)
	{
		g_g.tmp_pid = (g_g.tmp_pid << 1) | (sig == SIGUSR1);
		g_g.pid_bits++;
		if (g_g.pid_bits == 32)
		{
			g_g.pidclient = g_g.tmp_pid;
			g_g.receiving_pid = 0;
			g_g.tmp_pid = 0;
			g_g.pid_bits = 0;
		}
	}
	else
	{
		g_g.byte = (g_g.byte << 1) | (sig == SIGUSR1);
		g_g.bitcount++;
		if (g_g.bitcount == 8)
			me();
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

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
