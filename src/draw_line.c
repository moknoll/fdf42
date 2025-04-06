/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mknoll <mknoll@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 09:14:43 by moritzknoll       #+#    #+#             */
/*   Updated: 2025/04/06 10:56:50 by mknoll           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void plot_pixel(mlx_image_t *img, int x, int y, int color)
{
    if (x >= 0 && x < (int)img->width && y >= 0 && y < (int)img->height)
        mlx_put_pixel(img, x, y, color);
}

void draw_line(t_point a, t_point b, t_data *data)
{
    t_point delta = {abs(b.x - a.x), -abs(b.y - a.y), 0, 0};
    t_point sign = {a.x < b.x ? 1 : -1, a.y < b.y ? 1 : -1, 0, 0};
    t_point cur = a;
    int err = delta.x + delta.y;
    int e2;

    while (1)
    {
        float ratio;
        if (b.x != a.x)
            ratio = (float)(cur.x - a.x) / (b.x - a.x);
        else if (b.y != a.y)
            ratio = (float)(cur.y - a.y) / (b.y - a.y);
        else
            ratio = 0.0f;

        plot_pixel(data->img, cur.x, cur.y, get_gradient(a.color, b.color, ratio));

        if (cur.x == b.x && cur.y == b.y)
            break;

        e2 = 2 * err;
        if (e2 >= delta.y)
        {
            err += delta.y;
            cur.x += sign.x;
        }
        if (e2 <= delta.x)
        {
            err += delta.x;
            cur.y += sign.y;
        }
    }
}
