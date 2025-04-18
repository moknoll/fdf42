/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mknoll <mknoll@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:18:23 by moritzknoll       #+#    #+#             */
/*   Updated: 2025/04/06 11:08:57 by mknoll           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned int	i;
	const char		*char_s;

	char_s = (const char *)s;
	i = 0;
	while (i < n)
	{
		if (char_s[i] == (char)c)
		{
			return ((void *)(char_s + i));
		}
		i++;
	}
	return (NULL);
}
