/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moritzknoll <moritzknoll@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 07:45:58 by moritzknoll       #+#    #+#             */
/*   Updated: 2025/04/08 08:44:51 by moritzknoll      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	project(t_point p, t_map *map)
{
	t_point proj;
	float scale_x;
	int tmp;
	float scale_y;
	float scale;

	scale_x = (WIDTH * 0.5f) / map->width;
	scale_y = (HEIGHT * 0.5f) / map->height;
	scale = fminf(scale_x, scale_y) * 0.9f;
	tmp = p.x;
	proj.x = (tmp - p.y) * cosf(0.523599) * scale;
	proj.y = (tmp + p.y) * sinf(0.523599) * scale - p.z * (scale / 4.0f);
	proj.x += WIDTH / 2;
	proj.y += HEIGHT / 2;
	proj.color = p.color;
	return (proj);
}

void	update_line_position(t_point *p, t_line_vars *v)
{
	int	e2;

	e2 = 2 * v->err;
	if (e2 >= v->dy)
	{
		v->err += v->dy;
		p->x += v->sx;
	}
	if (e2 <= v->dx)
	{
		v->err += v->dx;
		p->y += v->sy;
	}
}
