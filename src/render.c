/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mknoll <mknoll@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 07:15:45 by moritzknoll       #+#    #+#             */
/*   Updated: 2025/04/08 14:10:49 by mknoll           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_wireframe(mlx_image_t *img, t_map *map)
{
	int	y;

	y = 0;
	while (y < map->height)
	{
		draw_row(img, map, y);
		y++;
	}
}

void	render_map(t_map *map)
{
	mlx_t			*mlx;
	mlx_image_t		*img;

	mlx = mlx_init(WIDTH, HEIGHT, "FdF", true);
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img)
	{
		mlx_terminate(mlx);
		return ;
	}
	if (!mlx)
		return ;
	calculate_colors(map);
	draw_wireframe(img, map);
	mlx_image_to_window(mlx, img, 0, 0);
	mlx_key_hook(mlx, handle_keyhook, mlx);
	mlx_close_hook(mlx, handle_closehook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}
