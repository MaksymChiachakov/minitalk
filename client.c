/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiacha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 13:28:22 by mchiacha          #+#    #+#             */
/*   Updated: 2025/11/25 13:48:14 by mchiacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <limits.h>
#include <sys/types.h>
#include <stdio.h>

int	ft_atoi(char *str)
{
	long long int	res;

	res = 0;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
		if (res > INT_MAX)
			return (-1);
	}
	return (res);
}

void	conv_bin(char *s, int pidserv)
{
	int	i;
	int	base;
	int	letra;

	i = 0;
	while (s[i])
	{
		base = 128;
		letra = s[i];
		while (base > 0)
		{
			if (letra >= base)
			{
				kill(pidserv, SIGUSR1);
				letra = letra - base;
			}
			else
				kill(pidserv, SIGUSR2);
			base = base / 2;
			usleep(200);
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	int	pidserv;

	if (argc != 3)
		return (-1);
	pidserv = ft_atoi(argv[1]);
	conv_bin(argv[2], pidserv);
	return (0);
}
