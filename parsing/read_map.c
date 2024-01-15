/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asettar <asettar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 02:23:29 by sakarkal          #+#    #+#             */
/*   Updated: 2024/01/12 20:23:45 by asettar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	check_in_border(int i, int j, t_map *map)
{
	if (is_a_member(map->map[i][j]) && map->map[i][j] != '1')
	{
		if (j == 0 || map->map[i][j + 1] == '\0')
			exit_err("Error\nInvalid map\n", map);
		if (i == 0 || i == map->height - 1)
			exit_err("Error\nInvalid map\n", map);
		if (!is_a_member(map->map[i][j + 1]))
			exit_err("Error\nInvalid map\n", map);
		if (!is_a_member(map->map[i][j - 1]))
			exit_err("Error\nInvalid map\n", map);
		if (!is_a_member(map->map[i + 1][j]))
			exit_err("Error\nInvalid map\n", map);
		if (!is_a_member(map->map[i - 1][j]))
			exit_err("Error\nInvalid map\n", map);
	}
}

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
					exit_err("Error\nMore than one player in the map\n\n", map);
				map->x = j;
				map->y = i;
				map->orientation = map->map[i][j];
			}
			if (!(is_a_member(map->map[i][j]) || map->map[i][j] == ' '))
				exit_err("Non valid elemnt!\n", map);
			check_in_border(i, j, map);
			j++;
		}
	}
	if (!map->x)
		exit_err("No Player in your map", map);
}

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

void	read_map(int fd, t_map *map)
{
	char	*line;
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
		exit_err("Error\nInvalid map\n", map);
	free(tmp);
	check_map_errors(map);
	fill_map(map);
}
