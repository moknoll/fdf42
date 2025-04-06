/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moritzknoll <moritzknoll@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 09:13:17 by moritzknoll       #+#    #+#             */
/*   Updated: 2025/04/06 09:13:19 by moritzknoll      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	extract_color(char *str)
{
	char	*hex_start;

	hex_start = ft_strchr(str, ',');
	if (!hex_start)
		return (0xFFFFFF); // Default: Weiß
	return (ft_atoi_base(hex_start + 1, 16));
}

t_point	*parse_line(char *line, int width)
{
	char	**split;
	t_point	*row;
	int		i;

	split = ft_split(line, ' ');
	if (!split)
		exit_error("ft_split failed");
	row = malloc(sizeof(t_point) * width);
	if (!row)
		return (free_split(split), NULL);
	i = 0;
	while (i < width && split[i])
	{
		row[i].z = ft_atoi(split[i]);
		row[i].color = extract_color(split[i]);
		free(split[i++]);
	}
	free(split);
	return (row);
}
