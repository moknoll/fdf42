/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moritzknoll <moritzknoll@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 08:18:00 by moritzknoll       #+#    #+#             */
/*   Updated: 2025/04/08 08:48:29 by moritzknoll      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	interpolate(int c1, int c2, float ratio)
{
	int	rgbs[3];
	int	rgbe[3];
	int	result;

	rgbs[0] = (c1 >> 16) & 0xFF;
	rgbs[1] = (c1 >> 8) & 0xFF;
	rgbs[2] = c1 & 0xFF;
	rgbe[0] = (c2 >> 16) & 0xFF;
	rgbe[1] = (c2 >> 8) & 0xFF;
	rgbe[2] = c2 & 0xFF;
	result = (((int)(rgbs[0] + ratio * (rgbe[0] - rgbs[0]))) << 16) |
			(((int)(rgbs[1] + ratio * (rgbe[1] - rgbs[1]))) << 8) |
			((int)(rgbs[2] + ratio * (rgbe[2] - rgbs[2])));
	return (result);
}

static int	get_color(float ratio)
{
	if (ratio < 0.2f)
		return (interpolate(0x4B79CF, 0x93C572, ratio / 0.2f));
	else if (ratio < 0.5f)
		return (interpolate(0x93C572, 0xE0C65E, (ratio - 0.2f) / 0.5f));
	else if (ratio < 0.8f)
		return (interpolate(0xE0C65E, 0xC35214, (ratio - 0.5f) / 0.3f));
	else
		return (interpolate(0xC35214, 0xFFFFFF, (ratio - 0.8f) / 0.2f));
}

static void	get_z_bounds(t_map *map, int *z_min, int *z_max)
{
	int y;
	int x;
	int z;

	*z_min = map->grid[0][0].z;
	*z_max = map->grid[0][0].z;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			z = map->grid[y][x].z;
			if (z < *z_min)
				*z_min = z;
			if (z > *z_max)
				*z_max = z;
			x++;
		}
		y++;
	}
}

void	calculate_colors(t_map *map)
{
	int		z_bounds[2];
	int		coords[2];
	float	ratio;

	get_z_bounds(map, &z_bounds[0], &z_bounds[1]);
	coords[0] = 0;
	while (coords[0] < map->height)
	{
		coords[1] = 0;
		while (coords[1] < map->width)
		{
			ratio = (float)(map->grid[coords[0]][coords[1]].z - z_bounds[0]) /
					(z_bounds[1] - z_bounds[0]);
			map->grid[coords[0]][coords[1]].color = get_color(ratio);
			coords[1]++;
		}
		coords[0]++;
	}
}
