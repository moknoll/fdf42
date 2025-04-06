/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mknoll <mknoll@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 09:13:45 by moritzknoll       #+#    #+#             */
/*   Updated: 2025/04/06 11:16:52 by mknoll           ###   ########.fr       */
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
static int ft_strcmp(const char *s1, const char *s2)
{
    unsigned char   c1;
    unsigned char   c2;

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

static bool has_fdf_extension(const char *filename)
{
    const char *dot;

    dot = ft_strrchr(filename, '.');  // Finde den letzten Punkt im Dateinamen
    if (!dot || dot == filename)      // Kein Punkt oder versteckte Datei (z. B. ".hidden")
        return false;
    return (ft_strcmp(dot, ".fdf") == 0);
}

int get_map_width(char *line)
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
	// Speicher von ft_split freigeben
	i = 0;
	while (tokens[i])
		free(tokens[i++]);
	free(tokens);
	return (width);
}

int get_map_height(const char *filename)
{
    int fd;
    char *line;
    int height = 0;

    fd = open(filename, O_RDONLY);
    if (fd == -1)
        exit_error("Failed to open file");

    // Liest die Datei Zeile für Zeile
    while ((line = get_next_line(fd)) != NULL)
    {
        height++;  // Zählt jede gelesene Zeile
        free(line);  // Gibt die gelesene Zeile wieder frei
    }

    close(fd);  // Schließt die Datei
    return height;  // Gibt die Anzahl der Zeilen (die Höhe der Map) zurück
}

t_map *parse_map(const char *filename)
{
    t_map *map;
    int fd;
    char *line;
    int i;

    if (!has_fdf_extension(filename))
        exit_error("Invalid file extension. Use .fdf");

    map = init_map(get_map_height(filename));
    if (!map)
        return NULL;

    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        free(map);
        exit_error("Failed to open map file");
    }

    line = get_next_line(fd);
    map->width = get_map_width(line);
    i = 0;

    while (i < map->height && line)
    {
        map->grid[i] = parse_line(line, map->width);
        free(line);
        if (!map->grid[i])
        {
            free_grid(map->grid, i);
            free(map);
            return NULL;
        }
        line = get_next_line(fd);
        i++;
    }
    close(fd);
    return map;
}


