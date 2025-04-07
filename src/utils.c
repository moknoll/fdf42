/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moritzknoll <moritzknoll@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 09:14:15 by moritzknoll       #+#    #+#             */
/*   Updated: 2025/04/07 11:07:13 by moritzknoll      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	exit_error(char *msg)
{
	ft_putendl_fd(msg, 2);
	exit(EXIT_FAILURE);
}

static int ft_isspace(char c)
{
	if(c == 32 ||(c >= 9 && c <= 13))
		return 1;
	return 0;
}

static int  get_digit(char c, int base)
{
	int digit;

	if (c >= '0' && c <= '9')
		digit = c - '0';
	else if (c >= 'a' && c <= 'f')
		digit = c - 'a' + 10;
	else if (c >= 'A' && c <= 'F')
		digit = c - 'A' + 10;
	else
		return (-1);

	return (digit < base ? digit : -1); //change
}

int ft_atoi_base(const char *str, int base)
{
	int result = 0;
	int sign = 1;
	int digit;

	if (!str || base < 2 || base > 16)
		return (0);
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
		sign = (*str++ == '-') ? -1 : 1; // change
	while ((digit = get_digit(*str, base)) >= 0)
	{
		result = result * base + digit;
		str++;
	}
	return (result * sign);
}

void	free_split(char **split_array)
{
	int i;
	if (!split_array)
		return ;
    i = 0;
    while (split_array[i])
    {
        free(split_array[i]);
        i++;
    }
    free(split_array);
}

void	free_map(t_map *map)
{
	int	y;

	if (!map)
		return ;
	y = 0;
	while (y < map->height)
	{
		if (map->grid[y])
			free(map->grid[y]);
		y++;
	}
	if (map->grid)
		free(map->grid);
	free(map);
}

void free_grid(t_point **grid, int height)
{
	int i;

	if (!grid)
		return;

	i = 0;
	while (i < height)
	{
		if (grid[i])
			free(grid[i]);
		i++;
	}
	free(grid);
}
