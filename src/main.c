/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mknoll <mknoll@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 07:19:49 by moritzknoll       #+#    #+#             */
/*   Updated: 2025/04/08 13:59:18 by mknoll           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_map	*map;

	if (argc != 2)
	{
		ft_putendl_fd("Usage: ./fdf <map.fdf>", 2);
		return (1);
	}
	map = parse_map(argv[1]);
	if (!map)
	{
		ft_putendl_fd("Error parsing failed", 2);
		free_gnl_buffer();
		return (1);
	}
	render_map(map);
	free_map(map);
	return (0);
}
