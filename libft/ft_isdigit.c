/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mknoll <mknoll@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:25:51 by mknoll            #+#    #+#             */
/*   Updated: 2025/04/08 13:47:28 by mknoll           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_isdigit(int c)
{
	if ((c >= '0' && c <= '9') || (c == 32 || (c >= 9 && c <= 13)))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}
