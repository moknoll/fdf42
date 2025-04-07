/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moritzknoll <moritzknoll@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 07:19:49 by moritzknoll       #+#    #+#             */
/*   Updated: 2025/04/07 12:23:14 by moritzknoll      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"

static bool is_in_window(t_point p)
{
	return (p.x >= 0 && p.x < WIDTH && p.y >= 0 && p.y < HEIGHT);
}

t_point project(t_point p, t_map *map)
{
	t_point proj;
	float scale_x = (WIDTH * 0.5f) / map->width;
	float scale_y = (HEIGHT * 0.5f) / map->height;
	float scale = fminf(scale_x, scale_y) * 0.9f;

	int tmp = p.x;
	proj.x = (tmp - p.y) * cosf(0.523599) * scale;  // cos(30°) für Isometrie
	proj.y = (tmp + p.y) * sinf(0.523599) * scale - p.z * (scale / 7.0f);  // sin
	proj.x += WIDTH / 2;
	proj.y += HEIGHT / 2;
	proj.color = p.color;
	return proj;
}

static void init_line_vars(t_line_vars *v, t_point p1, t_point p2)
{
	v->dx = abs(p2.x - p1.x);
	v->dy = -abs(p2.y - p1.y);
	v->sx = (p1.x < p2.x) ? 1 : -1;
	v->sy = (p1.y < p2.y) ? 1 : -1;
	v->err = v->dx + v->dy;
	v->steps = (v->dx > -v->dy) ? v->dx : -v->dy;
	v->z = (float)p1.z;
	if (v->steps != 0)
		v->z_step = ((float)p2.z - (float)p1.z) / v->steps;
	else
		v->z_step = 0;
}

static float fraction(float start, float end, float current)
{
    if (end != start)  // Vermeide Division durch Null
        return (current - start) / (end - start);
    return 0.0f;  // Rückgabe 0, wenn keine Differenz besteht
}

// Berechnet die Interpolation basierend auf der x- oder y-Dimension
static float function(float x, float y, t_point *a, t_point *b)
{
    int dx = b->x - a->x;
    int dy = b->y - a->y;
    float fraction_value;

    // Interpolationsrichtung anhand der größeren Dimension wählen
    if (abs(dx) > abs(dy))
        fraction_value = fraction(a->x, b->x, x);  // Interpolation entlang der x-Achse
    else
        fraction_value = fraction(a->y, b->y, y);  // Interpolation entlang der y-Achse

    return fraction_value;
}

// static int get_interpolated_color(t_point p1, t_point p2, float z)
// {
//     float dz = (float)(p2.z - p1.z);
//     float ratio = 0.0f;

//     if (dz != 0)
//         ratio = (z - (float)p1.z) / dz;

//     return interpolate(p1.color, p2.color, ratio);
// }

void draw_line(mlx_image_t *img, t_point p1, t_point p2)
{
    t_line_vars v;
    int e2;
    int color;
    float fraction_value;

    init_line_vars(&v, p1, p2);

    while (1)
    {
        if (p1.x >= 0 && p1.x < WIDTH && p1.y >= 0 && p1.y < HEIGHT)
        {
            // Berechne den Bruchteil der Linie
            fraction_value = function(p1.x, p1.y, &p1, &p2);

            // Berechne den interpolierten Farbwert
            color = interpolate(p1.color, p2.color, fraction_value);

            mlx_put_pixel(img, p1.x, p1.y, color);
        }

        if (p1.x == p2.x && p1.y == p2.y)
            break;

        e2 = 2 * v.err;
        if (e2 >= v.dy)
        {
            v.err += v.dy;
            p1.x += v.sx;
        }
        if (e2 <= v.dx)
        {
            v.err += v.dx;
            p1.y += v.sy;
        }
        v.z += v.z_step;
    }
}

void draw_wireframe(mlx_image_t *img, t_map *map)
{
	int y = 0;
	t_point p1, p2;

	while (y < map->height)
	{
		int x = 0;
		while (x < map->width)
		{
			if (x < map->width - 1)
			{
				p1 = project(map->grid[y][x], map);
				p2 = project(map->grid[y][x+1], map);
				if (is_in_window(p1) && is_in_window(p2))
					draw_line(img, p1, p2);
			}
			if (y < map->height - 1)
			{
				p1 = project(map->grid[y][x], map);
				p2 = project(map->grid[y+1][x], map);
				if (is_in_window(p1) && is_in_window(p2))
					draw_line(img, p1, p2);
			}
			x++;
		}
		y++;
	}
}
