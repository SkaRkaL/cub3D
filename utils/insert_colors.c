/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_colors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakarkal <sakarkal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 02:23:33 by sakarkal          #+#    #+#             */
/*   Updated: 2024/01/12 02:23:34 by sakarkal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	check_commas(char *str)
{
	int	i;
	int	commas;

	i = 0;
	commas = 0;
	while (str[i])
	{
		if (str[i] == ',')
			commas++;
		i++;
	}
	if (commas != 2)
		return (1);
	return (0);
}

void	insert_colors(char *path, t_map *map, int i)
{
	char	**color;
	int		rgb;

	if (check_commas(path))
		exit_err("Error\nInvalid color");
	color = ft_split(path, ',');
	rgb = set_color(color);
	if (rgb == 1)
		exit_err("Error\nInvalid color");
	*((int *)&map->c + (i - 4)) = rgb;
	check_isfree(color);
	color = NULL;
}
