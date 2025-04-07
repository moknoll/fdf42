/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moritzknoll <moritzknoll@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 08:18:00 by moritzknoll       #+#    #+#             */
/*   Updated: 2025/04/07 12:47:46 by moritzknoll      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int interpolate(int c1, int c2, float ratio)
{
	int r1;
	int g1;
	int b1;
	int r2;
	int g2;
	int b2;
	int r;
	int g;
	int b;

	r1 = (c1 >> 16) & 0xFF;
	g1 = (c1 >> 8) & 0xFF;
	b1 = c1 & 0xFF;
	r2 = (c2 >> 16) & 0xFF;
	g2 = (c2 >> 8) & 0xFF;
	b2 = c2 & 0xFF;
	r = r1 + ratio * (r2 - r1);
	g = g1 + ratio * (g2 - g1);
	b = b1 + ratio * (b2 - b1);
	return (r << 16) | (g << 8) | b;
}

static int get_color(float ratio)
{
	if (ratio < 0.2f)
		return interpolate(0xFFFFFF, 0xADD8E6, ratio / 0.2f);  // Weiß zu Hellblau
	else if (ratio < 0.4f)  // Niedrig
		return interpolate(0xADD8E6, 0xFFFF00, (ratio - 0.2f) / 0.2f);  // Hellblau zu Gelb
	else if (ratio < 0.6f)  // Mittel
		return interpolate(0xFFFF00, 0xFF6347, (ratio - 0.4f) / 0.2f);  // Gelb zu Tomatenrot
	else if (ratio < 0.8f)  // Hoch
		return interpolate(0xFF6347, 0xFF4500, (ratio - 0.6f) / 0.2f);  // Tomatenrot zu Orange-Red
	else  // Sehr hoch
		return interpolate(0xFF4500, 0xFF0000, (ratio - 0.8f) / 0.2f);  // Orange-Red zu Rot
}




static void get_z_bounds(t_map *map, int *z_min, int *z_max)
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

void calculate_colors(t_map *map)
{
    int z_min;
    int z_max;
    int x;
    int y;
    float ratio;

    // Hole die minimalen und maximalen Höhenwerte
    get_z_bounds(map, &z_min, &z_max);

    // Berechne den Farbverlauf basierend auf den Höhenwerten
    y = 0;
    while (y < map->height)
    {
        x = 0;
        while (x < map->width)
        {
            int z = map->grid[y][x].z;

            // Berechne das Verhältnis für den Farbverlauf (zwischen 0 und 1)
            ratio = (float)(z - z_min) / (z_max - z_min);

            // Berechne die Farbe basierend auf dem Verhältnis
            map->grid[y][x].color = get_color(ratio);
            x++;
        }
        y++;
    }
}
