/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddback.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moritzknoll <moritzknoll@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:22:50 by moritzknoll       #+#    #+#             */
/*   Updated: 2025/02/17 12:04:21 by moritzknoll      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*last;

	if (!lst)
	{
		return (NULL);
	}
	last = lst;
	while (last->next)
	{
		last = last->next;
	}
	return (last);
}

void ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list *last;

	last = *lst;
	if (!lst || !new)
		return;
	if (*lst == NULL) // Falls Liste leer ist, setze `new` als erstes Element
	{
		*lst = new;
		return;
	}
	while (last->next)
		last = last->next;
	last->next = new;
}
