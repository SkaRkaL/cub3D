/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_in_border.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakarkal <sakarkal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 02:23:04 by sakarkal          #+#    #+#             */
/*   Updated: 2024/01/12 02:32:11 by sakarkal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	check_in_border(int i, int j, t_map *map)
{
	if (is_a_member(map->map[i][j]) && map->map[i][j] != '1')
	{
		if (j == 0 || map->map[i][j + 1] == '\0')
			exit(printf("Error\n"));
		if (i == 0 || i == map->height - 1)
			exit(printf("Error again 1\n"));
		if (!is_a_member(map->map[i][j + 1]))
			exit(printf("Error again 2\n"));
		if (!is_a_member(map->map[i][j - 1]))
			exit(printf("Error again 3\n"));
		if (!is_a_member(map->map[i + 1][j]))
			exit(printf("Error again 4\n"));
		if (!is_a_member(map->map[i - 1][j]))
			exit(printf("Error again 5\n"));
	}
}
