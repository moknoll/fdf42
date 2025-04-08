#include "fdf.h"

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
	free_map(map);
	return (0);
}
