/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mknoll <mknoll@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 09:13:45 by moritzknoll       #+#    #+#             */
/*   Updated: 2025/04/08 13:37:06 by mknoll           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map	*init_map(int height)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
	{
		exit_error("malloc failed");
	}
	map->height = height;
	map->grid = malloc(sizeof(t_point *) * height);
	if (!map->grid)
	{
		free(map);
		exit_error("malloc failed for grid");
	}
	return (map);
}

int	ft_strcmp(const char *s1, const char *s2)
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

bool	has_fdf_extension(const char *filename)
{
	const char	*dot;

	dot = ft_strrchr(filename, '.');
	if (!dot || dot == filename)
		return (false);
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
	int		fd;
	char	*line;
	int		height;

	height = 0;
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
