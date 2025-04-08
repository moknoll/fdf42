/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mknoll <mknoll@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 09:14:15 by moritzknoll       #+#    #+#             */
/*   Updated: 2025/04/08 14:10:31 by mknoll           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	exit_error(char *msg)
{
	ft_putendl_fd(msg, 2);
	exit(EXIT_FAILURE);
}

static int	ft_isspace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

static int	get_digit(char c, int base)
{
	int	digit;

	if (c >= '0' && c <= '9')
		digit = c - '0';
	else if (c >= 'a' && c <= 'f')
		digit = c - 'a' + 10;
	else if (c >= 'A' && c <= 'F')
		digit = c - 'A' + 10;
	else
		return (-1);
	if (digit < base)
		return (digit);
	return (-1);
}

int	ft_atoi_base(const char *str, int base)
{
	int	result;
	int	sign;
	int	digit;

	sign = 1;
	result = 0;
	if (!str || base < 2 || base > 16)
		return (0);
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	digit = get_digit(*str, base);
	while (digit >= 0)
	{
		result = result * base + digit;
		str++;
		digit = get_digit(*str, base);
	}
	return (result * sign);
}

void	free_split(char **split_array)
{
	int	i;

	if (!split_array)
		return ;
	i = 0;
	while (split_array[i])
	{
		free(split_array[i]);
		split_array[i] = NULL;
		i++;
	}
	free(split_array);
}
