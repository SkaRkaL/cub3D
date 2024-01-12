/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_errs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakarkal <sakarkal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 02:23:06 by sakarkal          #+#    #+#             */
/*   Updated: 2024/01/12 02:23:07 by sakarkal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	check_map_errors(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	while (++i < map->height)
	{
		j = 0;
		while (map->map[i][j])
		{
			if (is_a_player(map->map[i][j]))
			{
				if (map->x != 0)
					exit(printf("ERROOOORRRR\n"));
				map->x = j;
				map->y = i;
			}
			if (!(is_a_member(map->map[i][j]) || map->map[i][j] == ' '))
				exit(printf("Non valid elemnt!\n"));
			check_in_border(i, j, map);
			j++;
		}
	}
	if (!map->x)
		exit(puts("No Player in your map"));
}
