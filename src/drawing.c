/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moritzknoll <moritzknoll@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 07:19:49 by moritzknoll       #+#    #+#             */
/*   Updated: 2025/04/08 08:43:42 by moritzknoll      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"

void	draw_line_loop(mlx_image_t *img, t_point p1, t_point p2, t_line_vars *v)
{
	int		color;
	float	fraction;

	while (1)
	{
		if (is_in_bounds(p1.x, p1.y))
		{
			fraction = function(p1.x, p1.y, &p1, &p2);
			color = interpolate(p1.color, p2.color, fraction);
			mlx_put_pixel(img, p1.x, p1.y, color);
		}
		if (p1.x == p2.x && p1.y == p2.y)
			break;
		update_line_position(&p1, v);
		v->z += v->z_step;
	}
}

void	draw_line(mlx_image_t *img, t_point p1, t_point p2)
{
	t_line_vars	v;

	init_line_vars(&v, p1, p2);
	draw_line_loop(img, p1, p2, &v);
}

void	draw_down(mlx_image_t *img, t_map *map, int x, int y)
{
	t_point	p1;
	t_point	p2;

	if (y < map->height - 1)
	{
		p1 = project(map->grid[y][x], map);
		p2 = project(map->grid[y + 1][x], map);
		if (is_in_window(p1) && is_in_window(p2))
			draw_line(img, p1, p2);
	}
}

void	draw_right(mlx_image_t *img, t_map *map, int x, int y)
{
	t_point	p1;
	t_point	p2;

	if (x < map->width - 1)
	{
		p1 = project(map->grid[y][x], map);
		p2 = project(map->grid[y][x + 1], map);
		if (is_in_window(p1) && is_in_window(p2))
			draw_line(img, p1, p2);
	}
}

void	draw_row(mlx_image_t *img, t_map *map, int y)
{
	int	x;

	x = 0;
	while (x < map->width)
	{
		draw_right(img, map, x, y);
		draw_down(img, map, x, y);
		x++;
	}
}

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
