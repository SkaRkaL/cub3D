/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakarkal <sakarkal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 02:23:35 by sakarkal          #+#    #+#             */
/*   Updated: 2024/01/12 02:27:49 by sakarkal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	fill_map(t_map *map)
{
	char	*spaces;
	int		line_length;
	int		i;

	i = 0;
	while (i < map->height)
	{
		line_length = ft_strlen(map->map[i]);
		if (line_length < map->width)
		{
			spaces = ft_repeat(' ', map->width - line_length);
			map->map[i] = ft_strjoin(map->map[i], spaces);
		}
		i++;
	}
}
