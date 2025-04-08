/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mknoll <mknoll@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 09:13:45 by moritzknoll       #+#    #+#             */
/*   Updated: 2025/04/08 14:12:19 by mknoll           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	validate_extension(const char *filename)
{
	if (!has_fdf_extension(filename))
		exit_error("Invalid file extension. Use .fdf");
}

static int	open_map_file(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		exit_error("Failed to open map file");
	return (fd);
}

static t_map	*fill_map_grid(int fd, t_map *map)
{
	char	*line;
	int		i;
	int		line_num;

	line = get_next_line(fd);
	if (!line)
		return (free(map), exit_error("Failed to read map file"),
			close(fd), NULL);
	map->width = get_map_width(line);
	i = 0;
	line_num = 1;
	while (i < map->height && line)
	{
		map->grid[i] = parse_line(line, map->width, line_num);
		if (!map->grid[i])
			return (free(line), free_grid(map->grid, i),
				free(map), close(fd), NULL);
		free(line);
		line = get_next_line(fd);
		i++;
		line_num++;
	}
	close(fd);
	return (map);
}

t_map	*parse_map(const char *filename)
{
	t_map	*map;
	int		fd;
	int		height;

	height = get_map_height(filename);
	validate_extension(filename);
	map = init_map(get_map_height(filename));
	if (height == 0 || !map)
	{
		free_map(map);
		exit_error("File is empty");
	}
	fd = open_map_file(filename);
	map = fill_map_grid(fd, map);
	return (map);
}
