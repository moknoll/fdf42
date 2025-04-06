/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mknoll <mknoll@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 07:33:33 by mknoll            #+#    #+#             */
/*   Updated: 2025/04/06 10:53:00 by mknoll           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


t_point project(t_point p)
{
    t_point proj;
    const float angle = 0.8f; // Isometrischer Winkel (~30°)

    proj.x = (p.x - p.y) * cosf(angle);
    proj.y = (p.x + p.y) * sinf(angle) - p.z;
    proj.z = 0; // 2D-Projektion benötigt keine z-Koordinate
    proj.color = p.color;
    return (proj);
}

void transform_grid(t_map *map, t_point **projected)
{
    int y = 0;

    while (y < map->height)
    {
        int x = 0;
        while (x < map->width)
        {
            projected[y][x] = project(map->grid[y][x]);
            x++;
        }
        y++;
    }
}
