/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures_color.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakarkal <sakarkal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 02:23:39 by sakarkal          #+#    #+#             */
/*   Updated: 2024/01/12 02:37:04 by sakarkal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	check_textures_colors(char *trimmed_line, short *flag, t_map *map)
{
	static char		*kk[6] = {"NO", "SO", "WE", "EA", "C", "F"};
	static short	kk_flag[6] = {1, 2, 4, 8, 16, 32};
	t_var			var;

	var.dir = ft_strtok(trimmed_line, " ");
	var.path = ft_strtok(NULL, "");
	if (var.path == NULL)
		exit_err("Error\nInvalid path");
	var.i = -1;
	while (++var.i < 6)
	{
		if (!ft_strncmp(var.dir, kk[var.i], ft_strlen(kk[var.i])))
		{
			if (*flag & kk_flag[var.i])
				exit_err("Error\nDuplicate key");
			*flag |= kk_flag[var.i];
			if (var.i < 4)
				*((char **)&map->no + var.i) = ft_strdup(var.path);
			else
				insert_colors(var.path, map, var.i);
		}
	}
	free(var.path);
	free(var.dir);
}
