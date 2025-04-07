/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moritzknoll <moritzknoll@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 09:13:23 by moritzknoll       #+#    #+#             */
/*   Updated: 2025/04/07 11:32:45 by moritzknoll      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

/* Standard-Bibliotheken */
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

/* Fenster-Einstellungen */
# define WIDTH 1280
# define HEIGHT 720

/* Struktur für 3D-Punkte + Farbe */
typedef struct s_point
{
    int     x;
    int     y;
    int     z;
    int     color;
}           t_point;

/* Struktur für die Map */
typedef struct s_map
{
    int     width;
    int     height;
    t_point **grid;
    int     z_min;
    int     z_max;
    mlx_t*  mlx;
}           t_map;

typedef struct s_line_vars
{
    int dx;
    int dy;
    int sx;
    int sy;
    int err;
    int steps;
    float z;
    float z_step;
}           t_line_vars;

/* ---- PARSING ---- */
t_map      *parse_map(const char *filename);
// int         validate_map_line(char *line, int width);
t_point	*parse_line(char *line, int width, int line_num);

/* ---- GRAPHICS ---- */
// Projektion
t_point     project(t_point p, t_map *map);

// Zeichnen
void        render_map(t_map *map);
void draw_wireframe(mlx_image_t *img, t_map *map);
void        draw_line(mlx_image_t *img, t_point p1, t_point p2);
void calculate_colors(t_map *map);
int interpolate(int c1, int c2, float ratio);

// Hilfsfunktionen
int         get_height_color(int z, t_map *map);  // Für Farbverläufe
void        center_map(t_map *map);               // Zentrierung

/* ---- UTILS ---- */
void        free_map(t_map *map);
void        exit_error(char *msg);
int         ft_atoi_base(const char *str, int base);
void	free_grid(t_point **grid, int height);
void    free_split(char **split_array);

/* ---- MLX42 HOOKS ---- */
void        hook_keys(mlx_key_data_t keydata, void *param);
void        hook_resize(int32_t width, int32_t height, void *param);

#endif
