/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mknoll <mknoll@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 09:13:23 by moritzknoll       #+#    #+#             */
/*   Updated: 2025/04/08 14:00:11 by mknoll           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

/* Standard-Libs */
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

/* Window-settings */
# define WIDTH 1280
# define HEIGHT 720

/* structs */
typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	color;
}	t_point;

typedef struct s_map
{
	int			width;
	int			height;
	t_point		**grid;
	int			z_min;
	int			z_max;
	mlx_t		*mlx;
}	t_map;

typedef struct s_line_vars
{
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
	int		steps;
	float	z;
	float	z_step;
}	t_line_vars;

/* ---- PARSING ---- */
t_map	*parse_map(const char *filename);
t_map	*init_map(int height);
t_point	*parse_line(char *line, int width, int line_num);
int		ft_strcmp(const char *s1, const char *s2);
bool	has_fdf_extension(const char *filename);
int		get_map_width(char *line);
int		get_map_height(const char *filename);

/* ---- GRAPHICS ---- */
t_point	project(t_point p, t_map *map);
void	draw_row(mlx_image_t *img, t_map *map, int y);
void	render_map(t_map *map);
void	draw_wireframe(mlx_image_t *img, t_map *map);
void	draw_line(mlx_image_t *img, t_point p1, t_point p2);
void	calculate_colors(t_map *map);
int		interpolate(int c1, int c2, float ratio);
void	update_line_position(t_point *p, t_line_vars *v);

/* ---- Drawing Utils ----*/
int		is_in_bounds(int x, int y);
void	init_line_vars(t_line_vars *v, t_point p1, t_point p2);
float	function(float x, float y, t_point *a, t_point *b);
bool	is_in_window(t_point p);

/* ---- UTILS ---- */
void	free_map(t_map *map);
void	exit_error(char *msg);
int		ft_atoi_base(const char *str, int base);
void	free_grid(t_point **grid, int height);
void	free_split(char **split_array);
size_t	ft_strspn(const char *s, const char *accept);

/* ---- MLX42 HOOKS ---- */
void	handle_closehook(void *param);
void	handle_keyhook(mlx_key_data_t keydata, void *param);

#endif
