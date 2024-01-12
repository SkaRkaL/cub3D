/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakarkal <sakarkal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 02:23:27 by sakarkal          #+#    #+#             */
/*   Updated: 2024/01/12 02:23:28 by sakarkal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	read_textures(int fd, t_map *map)
{
	short	flag;
	short	full_flag;
	int		i;
	char	*line;
	char	*trimmed_line;

	flag = 0;
	full_flag = 1 | 2 | 4 | 8 | 16 | 32;
	while (flag != full_flag)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		trimmed_line = ft_strtrim(line, "\n \t");
		if (!trimmed_line || ft_strlen(trimmed_line) == 0)
		{
			free(trimmed_line);
			free(line);
			continue ;
		}
		check_textures_colors(trimmed_line, &flag, map);
		free(trimmed_line);
		free(line);
	}
	check_duplicates(flag, full_flag);
}
