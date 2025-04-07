/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moritzknoll <moritzknoll@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 07:15:45 by moritzknoll       #+#    #+#             */
/*   Updated: 2025/04/07 12:25:27 by moritzknoll      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"

void set_background(mlx_image_t *img, int color)
{
    int x, y;
    for (y = 0; y < HEIGHT; y++)
    {
        for (x = 0; x < WIDTH; x++)
        {
            mlx_put_pixel(img, x, y, color);  // Setze das Pixel auf die gewünschte Farbe
        }
    }
}

void render_map(t_map *map)
{
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "FdF", true);
	mlx_image_t* img = mlx_new_image(mlx, WIDTH, HEIGHT);
	set_background(img, 0x000000);
	calculate_colors(map);
	draw_wireframe(img, map);
	mlx_image_to_window(mlx, img, 0, 0);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}

