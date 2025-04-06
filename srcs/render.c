/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moritzknoll <moritzknoll@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 09:15:28 by moritzknoll       #+#    #+#             */
/*   Updated: 2025/04/06 09:15:30 by moritzknoll      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	render(t_data *data)
{
	t_point	**proj;
	int		y;
	int		x;

	proj = malloc(sizeof(t_point *) * data->map->height);
	y = 0;
	while (y < data->map->height)
	{
		proj[y] = malloc(sizeof(t_point) * data->map->width);
		x = 0;
		while (x < data->map->width)
		{
			proj[y][x] = project(data->map->grid[y][x], data->map);
			if (x > 0)
				draw_line(proj[y][x - 1], proj[y][x], &data->img);
			if (y > 0)
				draw_line(proj[y - 1][x], proj[y][x], &data->img);
			x++;
		}
		y++;
	}
	free_grid(proj, data->map->height); // Hilfsfunktion zum Freigeben
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}
