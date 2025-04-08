/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mknoll <mknoll@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 07:42:15 by moritzknoll       #+#    #+#             */
/*   Updated: 2025/04/08 14:14:43 by mknoll           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	is_in_bounds(int x, int y)
{
	return (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT);
}

static float	fraction(float start, float end, float current)
{
	if (end != start)
		return ((current - start) / (end - start));
	return (0.0f);
}

void	init_line_vars(t_line_vars *v, t_point p1, t_point p2)
{
	v->dx = abs(p2.x - p1.x);
	v->dy = -abs(p2.y - p1.y);
	if (p1.x < p2.x)
		v->sx = 1;
	else
		v->sx = -1;
	if (p1.y < p2.y)
		v->sy = 1;
	else
		v->sy = -1;
	v->err = v->dx + v->dy;
	if (v->dx > -v->dy)
		v->steps = v->dx;
	else
		v->steps = -v->dy;
	v->z = (float)p1.z;
	if (v->steps != 0)
		v->z_step = ((float)p2.z - (float)p1.z) / v->steps;
	else
		v->z_step = 0;
}

float	function(float x, float y, t_point *a, t_point *b)
{
	int		dx;
	int		dy;
	float	fraction_value;

	dx = b->x - a->x;
	dy = b->y - a->y;
	if (abs(dx) > abs(dy))
		fraction_value = fraction(a->x, b->x, x);
	else
		fraction_value = fraction(a->y, b->y, y);
	return (fraction_value);
}

bool	is_in_window(t_point p)
{
	return (p.x >= 0 && p.x < WIDTH && p.y >= 0 && p.y < HEIGHT);
}
