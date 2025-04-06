/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mknoll <mknoll@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 09:16:00 by moritzknoll       #+#    #+#             */
/*   Updated: 2025/04/06 11:37:07 by mknoll           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int main(int argc, char **argv)
{
    t_data data;

    if (argc != 2)
        exit_error("Usage: ./fdf <map.fdf>");

    // MLX Initialisierung (mit allen benötigten Parametern)
    data.mlx = mlx_init(WIDTH, HEIGHT, "FDF", false);
    if (!data.mlx)
        exit_error("MLX initialization failed");
    // Map Parsing
    data.map = parse_map(argv[1]);
    if (!data.map)
        exit_error("Map parsing failed");

    // Image erstellen (MLX42 verwendet direkt mlx_image_t)
    data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
    if (!data.img)
        exit_error("Image creation failed");

    // Image ins Fenster einfügen
    if (mlx_image_to_window(data.mlx, data.img, 0, 0) < 0)
        exit_error("Failed to put image to window");

    render(&data);
    mlx_loop(data.mlx);
    mlx_terminate(data.mlx);
    return (0);
}
