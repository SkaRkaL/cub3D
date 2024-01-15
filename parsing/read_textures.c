/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakarkal <sakarkal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 02:23:27 by sakarkal          #+#    #+#             */
/*   Updated: 2024/01/15 20:38:30 by sakarkal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

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
	return (r << 24 | g << 16 | b << 8 | 255);
}

void	insert_colors(char *path, t_map *map, int i)
{
	char	**color;
	int		rgb;

	if (check_commas(path))
		exit_err("Error\nInvalid color", map);
	color = ft_split(path, ',');
	rgb = set_color(color);
	if (rgb == 1)
		exit_err("Error\nInvalid color", map);
	*((int *)&map->c + (i - 4)) = rgb;
	check_isfree(color);
	color = NULL;
}

void	check_textures_colors(char *trimmed_line, short *flag, t_map *map)
{
	static char		*kk[6] = {"NO", "SO", "WE", "EA", "C", "F"};
	static short	kk_flag[6] = {1, 2, 4, 8, 16, 32};
	t_var			var;

	var.dir = ft_strtok(trimmed_line, " ");
	var.path = ft_strtok(NULL, "");
	if (var.path == NULL)
		exit_err("Error\nInvalid path", map);
	var.i = -1;
	while (++var.i < 6)
	{
		if (!ft_strncmp(var.dir, kk[var.i], ft_strlen(var.dir)))
		{
			if (*flag & kk_flag[var.i])
				exit_err("Error\nDuplicate key", map);
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

void	check_missing_key(short flag, short full_flag, t_map *map)
{
	static char		*kk[6] = {"NO", "SO", "WE", "EA", "C", "F"};
	static short	kk_flag[6] = {1, 2, 4, 8, 16, 32};
	int				i;

	if (flag != full_flag)
	{
		i = 0;
		while (i < 6)
		{
			if (!(flag & kk_flag[i]))
				printf("missing [ %s ] key \n", kk[i]);
			i++;
		}
		exit_err("Error\nMissing key", map);
	}
}

void	read_textures(t_map *map)
{
	short	flag;
	short	full_flag;
	char	*line;
	char	*trimmed_line;

	flag = 0;
	full_flag = 1 | 2 | 4 | 8 | 16 | 32;
	while (flag != full_flag)
	{
		line = get_next_line(map->fd);
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
	check_missing_key(flag, full_flag, map);
}
