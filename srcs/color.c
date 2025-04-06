/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moritzknoll <moritzknoll@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 09:15:46 by moritzknoll       #+#    #+#             */
/*   Updated: 2025/04/06 09:15:48 by moritzknoll      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_gradient(int start, int end, float ratio)
{
	int	r;
	int	g;
	int	b;

	if (ratio > 1)
		ratio = 1;
	r = ((end >> 16) & 0xFF) * ratio + ((start >> 16) & 0xFF) * (1 - ratio);
	g = ((end >> 8) & 0xFF) * ratio + ((start >> 8) & 0xFF) * (1 - ratio);
	b = (end & 0xFF) * ratio + (start & 0xFF) * (1 - ratio);
	return (r << 16 | g << 8 | b);
}
