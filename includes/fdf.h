/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moritzknoll <moritzknoll@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 09:13:23 by moritzknoll       #+#    #+#             */
/*   Updated: 2025/04/06 09:13:26 by moritzknoll      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "../libft/libft.h"

typedef struct s_point
{
	int	z;
	int	color;
}	t_point;

typedef struct s_map
{
	int		width;
	int		height;
	t_point	**grid;
}	t_map;

// Parsing
int		get_map_height(const char *filename);
int		get_map_width(char *line);
t_map	*parse_map(const char *filename);

// Farb-Parsing
int		extract_color(char *str);
t_point	*parse_line(char *line, int width);

// Utils
void	free_grid(t_point **grid, int height);
void	exit_error(char *msg);

#endif
