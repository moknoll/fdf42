/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mknoll <mknoll@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 09:13:23 by moritzknoll       #+#    #+#             */
/*   Updated: 2025/04/06 11:33:29 by mknoll           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdio.h>
# include <math.h>
# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

# define WIDTH 800
# define HEIGHT 600

typedef struct s_point {
    int x;
    int y;
    int z;
    int color;
} t_point;

typedef struct s_map {
    int width;
    int height;
    t_point **grid;
} t_map;

typedef struct s_data {
    mlx_t* mlx;
    mlx_image_t* img;
    t_map* map;
} t_data;

/* --- Funktionsprototypen --- */
// Parsing
int     get_map_height(const char *filename);
int     get_map_width(char *line);
t_map	*parse_map(const char *filename);

// Farb-Parsing
t_point *parse_line(char *line, int width);
int     get_gradient(int start, int end, float ratio);

// Utils
void    free_grid(t_point **grid, int height);
void    exit_error(char *msg);
int     ft_atoi_base(const char *str, int base);
void    free_split(char **split_array);

// Drawing
void    draw_line(t_point a, t_point b, t_data *data);
void    render(t_data *data);

// Projection
t_point project(t_point p);

#endif
