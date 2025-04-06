/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moritzknoll <moritzknoll@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 09:13:45 by moritzknoll       #+#    #+#             */
/*   Updated: 2025/04/06 09:14:03 by moritzknoll      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static t_map	*init_map(int height)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		exit_error("malloc failed");
	map->height = height;
	map->grid = malloc(sizeof(t_point *) * height);
	if (!map->grid)
		return (free(map), NULL);
	return (map);
}

t_map	*parse_map(const char *filename)
{
	t_map	*map;
	int		fd;
	char	*line;
	int		i;

	if (ft_strncmp(filename + ft_strlen(filename) - 4, ".fdf", 4) != 0)
		exit_error("Invalid file extension. Use .fdf");
	map = init_map(get_map_height(filename));
	if (!map)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (free(map), NULL);
	line = get_next_line(fd);
	map->width = get_map_width(line);
	i = 0;
	while (i < map->height && line)
	{
		map->grid[i] = parse_line(line, map->width);
		free(line);
		if (!map->grid[i++])
			return (free_grid(map->grid, i - 1), free(map), NULL);
		line = get_next_line(fd);
	}
	close(fd);
	return (map);
}y
