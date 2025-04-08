/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moritzknoll <moritzknoll@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 07:15:45 by moritzknoll       #+#    #+#             */
/*   Updated: 2025/04/08 07:07:02 by moritzknoll      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"

void render_map(t_map *map)
{
	mlx_t* mlx;
	mlx_image_t* img;

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
