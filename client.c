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

// Наш ft_atoi для контатування/зміни строки в число 
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

// Конвертація бітів
void	conv_bin(char *s, int pidserv)
{
	int	i;
	int	base;
	int	letra;

	i = 0;
	while (s[i])
	{
		base = 128; // Наша база 128
		letra = s[i]; // Наша letra дорівнює літері у строці s, присвоєння значення
		while (base > 0) // Цикл працює до тих пір поки база більше 0
		{
			if (letra >= base) // Якщо літера більша або дорівнює нашій базі (128)
			{
				kill(pidserv, SIGUSR1); // Відправляємо 1 на сервер
				letra = letra - base; // Віднімаємо значення бази від значення літери 
			}
			else // В іншому випадку (якщо база більша літери)
				kill(pidserv, SIGUSR2); // Відправляємо 0 на сервер
			base = base / 2; // Ділимо базу на 2 при кожному повторі циклу
			usleep(200); // Спимо 200 мікросекунд
		}
		i++; // Рухаємось у циклі
	}
}

int	main(int argc, char **argv)
{
	int	pidserv;

	if (argc != 3)
		return (-1);
	pidserv = ft_atoi(argv[1]); // Перетворюємо аргумент який ми даємо в число щоб далі з ним працювати
	conv_bin(argv[2], pidserv); // Запускаємо функцію з нашою строкою та pid серверу
	return (0);
}
