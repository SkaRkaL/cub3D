/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakarkal <sakarkal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 02:23:29 by sakarkal          #+#    #+#             */
/*   Updated: 2024/01/12 02:28:09 by sakarkal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	read_map(int fd, t_map *map)
{
	char	*line;
	char	*trimmed_line;
	char	*tmp;
	bool	is_map;

	is_map = false;
	tmp = ft_strdup("");
	while (true)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (empty_line(line, map, &is_map))
			continue ;
		tmp = ft_strjoin(tmp, line);
		map->height++;
	}
	map->map = ft_split(tmp, '\n');
	if (map->map == NULL)
		exit(printf("Error\nInvalid map\n"));
	free(tmp);
}
