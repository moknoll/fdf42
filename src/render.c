/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mknoll <mknoll@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 09:15:28 by moritzknoll       #+#    #+#             */
/*   Updated: 2025/04/06 11:26:55 by mknoll           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void render(t_data *data)
{
    t_point **proj;
    int y;
    int x;

    // Speicher für projizierte Punkte allokieren
    proj = malloc(sizeof(t_point *) * data->map->height);
    if (!proj)
        exit_error("Memory allocation failed");

    y = 0;
    while (y < data->map->height)
    {
        proj[y] = malloc(sizeof(t_point) * data->map->width);
        if (!proj[y])
            exit_error("Memory allocation failed");

        x = 0;
        while (x < data->map->width)
        {
            proj[y][x] = project(data->map->grid[y][x]);

            // Horizontale Linien zeichnen
            if (x > 0)
                draw_line(proj[y][x-1], proj[y][x], data);

            // Vertikale Linien zeichnen
            if (y > 0)
                draw_line(proj[y-1][x], proj[y][x], data);

            x++;
        }
        y++;
    }

    // Speicher freigeben
    y = 0;
    while (y < data->map->height)
    {
        free(proj[y]);
        y++;
    }
    free(proj);

    // Bild anzeigen
    if (mlx_image_to_window(data->mlx, data->img, 0, 0) < 0)
        exit_error("Failed to display image");
}
