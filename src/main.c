#include "fdf.h"

// void print_map(t_map *map)
// {
//     int y = 0;
//     while (y < map->height)
//     {
//         int x = 0;
//         while (x < map->width)
//         {
//             x++;
//         }
//         y++;
//     }
// }

int	main(int argc, char **argv)
{
	t_map	*map;

	if (argc != 2)
	{
		ft_putendl_fd("Usage: ./fdf <map.fdf>", 2);
		return (1);
	}

	map = parse_map(argv[1]);
	if (!map)
	{
		ft_putendl_fd("Error parsing failed", 2);
		return (1);
	}
	render_map(map);
	// print_map(map);
	free_map(map);
	return (0);
}
