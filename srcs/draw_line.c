/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moritzknoll <moritzknoll@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 09:14:43 by moritzknoll       #+#    #+#             */
/*   Updated: 2025/04/06 09:14:56 by moritzknoll      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void	plot_pixel(t_img *img, int x, int y, int color)
{
	char	*pixel;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
		*(unsigned int *)pixel = color;
	}
}

void	draw_line(t_point a, t_point b, t_img *img)
{
	t_point	delta;
	t_point	sign;
	t_point	cur;
	int		err;
	int		e2;

	delta.x = abs(b.x - a.x);
	delta.y = -abs(b.y - a.y);
	sign.x = (a.x < b.x) ? 1 : -1;
	sign.y = (a.y < b.y) ? 1 : -1;
	err = delta.x + delta.y;
	cur = a;
	while (1)
	{
		plot_pixel(img, cur.x, cur.y, get_gradient(a.color, b.color,
			(float)(cur.x - a.x) / (b.x - a.x)));
		if (cur.x == b.x && cur.y == b.y)
			break ;
		e2 = 2 * err;
		if (e2 >= delta.y && (err += delta.y) && (cur.x += sign.x));
		if (e2 <= delta.x && (err += delta.x) && (cur.y += sign.y));
	}
}
