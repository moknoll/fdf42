/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mknoll <mknoll@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 09:14:15 by moritzknoll       #+#    #+#             */
/*   Updated: 2025/04/06 10:58:04 by mknoll           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_grid(t_point **grid, int height)
{
	int	i;

	i = 0;
	while (i < height)
		free(grid[i++]);
	free(grid);
}

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
        return (-1); // Ungültiges Zeichen

    return (digit < base ? digit : -1);
}

int ft_atoi_base(const char *str, int base)
{
    int result = 0;
    int sign = 1;
    int digit;

    if (!str || base < 2 || base > 16)
        return (0);

    // Whitespace überspringen
    while (ft_isspace(*str))
        str++;

    // Vorzeichen behandeln
    if (*str == '-' || *str == '+')
        sign = (*str++ == '-') ? -1 : 1;

    // Ziffern parsen
    while ((digit = get_digit(*str, base)) >= 0)
    {
        result = result * base + digit;
        str++;
    }

    return (result * sign);
}

void    free_split(char **split_array)
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
