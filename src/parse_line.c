/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mknoll <mknoll@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 09:13:17 by moritzknoll       #+#    #+#             */
/*   Updated: 2025/04/08 11:41:09 by mknoll           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	extract_color(char *str)
{
	char	*hex_start;

	hex_start = ft_strchr(str, ',');
	if (!hex_start)
		return (0xFFFFFF);
	hex_start = ft_strnstr(hex_start, "0x", 5);
	if (!hex_start)
		return (0xFFFFFF);
	return (ft_atoi_base(hex_start + 2, 16));
}

static bool	is_valid_number(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && str[i] != ',')
		if (!ft_isdigit(str[i++]))
			return (false);
	return (true);
}

static int	validate_and_split(char *line, int width, char ***split)
{
	int		i;
	char	*trimmed_line;

	trimmed_line = ft_strtrim(line, " \t\n\r");
	if (!trimmed_line)
		return (0);
	*split = ft_split(trimmed_line, ' ');
	free(trimmed_line);
	if (!*split)
		return (0);
	i = 0;
	while ((*split)[i])
		i++;
	if (i != width)
		return (free_split(*split), 0);
	i = 0;
	while (i < width)
	{
		if (!is_valid_number((*split)[i++]))
			return (free_split(*split), 0);
	}
	return (1);
}

t_point	*parse_line(char *line, int width, int line_num)
{
	char	**split;
	t_point	*row;
	int		i;

	if (!line || ft_strspn(line, " \t\n\r") == ft_strlen(line))
		return (NULL);
	if (!validate_and_split(line, width, &split))
		return (NULL);
	row = malloc(sizeof(t_point) * width);
	if (!row)
		return (free_split(split), NULL);
	i = 0;
	while (i < width)
	{
		row[i].x = i - width / 2;
		row[i].y = line_num - width / 2;
		row[i].z = ft_atoi(split[i]);
		row[i].color = extract_color(split[i]);
		free(split[i]);
		i++;
	}
	free(split);
	return (row);
}
