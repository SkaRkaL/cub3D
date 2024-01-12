/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakarkal <sakarkal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 02:23:25 by sakarkal          #+#    #+#             */
/*   Updated: 2024/01/12 02:28:30 by sakarkal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	invalid_number(char *str)
{
	int	i;
	int	start_number;

	i = 0;
	while (str[i] == '0')
		i++;
	start_number = i;
	while (str[i])
	{
		if (*(str + i) < '0' || *(str + i) > '9')
			return (0);
		i++;
	}
	if (i - start_number > 3)
		return (0);
	return (1);
}

int	set_color(char **color)
{
	int	i;
	int	r;
	int	g;
	int	b;

	i = 0;
	while (color[i])
	{
		if (!invalid_number(color[i]))
			return (1);
		i++;
	}
	if (i != 3)
		return (1);
	r = ft_atoi(color[0]);
	g = ft_atoi(color[1]);
	b = ft_atoi(color[2]);
	if (r > 255 || g > 255 || b > 255)
		return (1);
	if (r < 0 || g < 0 || b < 0)
		return (1);
	return (r << 24 | g << 16 | b << 8 | 1);
}
