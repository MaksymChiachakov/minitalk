/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiacha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 13:36:18 by mchiacha          #+#    #+#             */
/*   Updated: 2025/11/25 14:28:19 by mchiacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h> 
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>

void	ft_putchar(int c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int nb)
{
	if (nb > 9)
	{
		ft_putnbr(nb / 10);
		nb = nb % 10;
	}
	if (nb <= 9)
		ft_putchar('0' + nb);
}

void	conv_text(char *s)
{
	int	i;
	int	value;

	i = 0;
	value = 0;
	while (i < 8)
	{
		value = value * 2 + (s[i] == '1');
		i++;
	}
	write(1, &value, 1);
}

void	alm_bin(int sig)
{
	static int	i;
	static char	c[8];

	if (sig == SIGUSR1)
		c[i] = '1';
	else
		c[i] = '0';
	i++;
	if (i == 8)
	{
		conv_text(c);
		i = 0;
	}
}

int	main(void)
{
	getpid();
	ft_putnbr(getpid());
	write(1, "\n", 1);
	signal(SIGUSR1, alm_bin);
	signal(SIGUSR2, alm_bin);
	while (1)
		usleep(100);
	return (0);
}
