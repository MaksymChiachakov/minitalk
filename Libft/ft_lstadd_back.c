/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiacha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:09:17 by mchiacha          #+#    #+#             */
/*   Updated: 2025/11/07 11:13:47 by mchiacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *newnode)
{
	t_list	*last;

	if (!lst || !newnode)
		return ;
	if (!*lst)
	{
		*lst = newnode;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = newnode;
}
