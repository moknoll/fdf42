#include "fdf.h"

t_point	project(t_point p, t_map *map)
{
	t_point	proj;
	float	angle;

	angle = 0.8; // Isometrischer Winkel (~30°)
	proj.x = (p.x - p.y) * cos(angle);
	proj.y = (p.x + p.y) * sin(angle) - p.z;
	proj.color = p.color;
	return (proj);
}

void	transform_grid(t_map *map, t_point **projected)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			projected[y][x] = project(map->grid[y][x], map);
			x++;
		}
		y++;
	}
}
