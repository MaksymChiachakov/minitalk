/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiacha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:15:29 by mchiacha          #+#    #+#             */
/*   Updated: 2025/11/07 12:04:04 by mchiacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*cur;

	if (!lst || !*lst)
		return ;
	cur = *lst;
	while (cur)
	{
		tmp = cur->next;
		if (del)
			del(cur->content);
		free(cur);
		cur = tmp;
	}
	*lst = NULL;
}
