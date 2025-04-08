/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moritzknoll <moritzknoll@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 09:13:45 by moritzknoll       #+#    #+#             */
/*   Updated: 2025/04/08 08:43:31 by moritzknoll      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

static int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	c1;
	unsigned char	c2;

	while (*s1 && *s2)
	{
		c1 = (unsigned char)*s1;
		c2 = (unsigned char)*s2;
		if (c1 != c2)
			return (c1 - c2);
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

static bool	has_fdf_extension(const char *filename)
{
	const char *dot;

	dot = ft_strrchr(filename, '.');
	if (!dot || dot == filename)
		return false;
	return (ft_strcmp(dot, ".fdf") == 0);
}

int	get_map_width(char *line)
{
	int		width;
	char	**tokens;
	int		i;

	width = 0;
	tokens = ft_split(line, ' ');
	if (!tokens)
		exit_error("ft_split failed in get_map_width");
	while (tokens[width])
		width++;
	i = 0;
	while (tokens[i])
		free(tokens[i++]);
	free(tokens);
	return (width);
}

int	get_map_height(const char *filename)
{
	int fd;
	char *line;
	int height = 0;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		exit_error("Failed to open file");
	line = get_next_line(fd);
	while (line != NULL)
	{
		height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (height);
}

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
		return(exit_error("Failed to read map file"), close(fd), free(map), NULL);
	map->width = get_map_width(line);
	i = 0;
	line_num = 1;
	while (i < map->height && line)
	{
		map->grid[i] = parse_line(line, map->width, line_num);
		free(line);
		if (!map->grid[i])
			return (free_grid(map->grid, i), free(map), NULL);
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

	validate_extension(filename);
	map = init_map(get_map_height(filename));
	if (!map)
		exit_error("File is empty");
	fd = open_map_file(filename);
	map = fill_map_grid(fd, map);
	return (map);
}
