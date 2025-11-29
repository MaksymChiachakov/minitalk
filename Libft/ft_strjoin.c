/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiacha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:09:40 by mchiacha          #+#    #+#             */
/*   Updated: 2025/11/06 12:56:03 by mchiacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	l1;
	size_t	l2;
	char	*res;
	size_t	i;

	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	i = 0;
	res = malloc(l1 + l2 + 1);
	if (!res)
		return (NULL);
	while (i < l1)
	{
		res[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < l2)
	{
		res[l1 + i] = s2[i];
		i++;
	}
	res[l1 + l2] = '\0';
	return (res);
}
