/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_empty_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakarkal <sakarkal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 02:23:01 by sakarkal          #+#    #+#             */
/*   Updated: 2024/01/12 02:31:48 by sakarkal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	empty_line(char *line, t_map *map, bool *is_map)
{
	int		line_length;
	char	*trimmed_line;

	line_length = ft_strlen(line);
	if (line[line_length - 1] == '\n')
		line_length--;
	if (line_length > map->width)
		map->width = line_length;
	trimmed_line = ft_strtrim(line, "\t ");
	if (ft_strlen(trimmed_line) == 1 && *is_map == false)
	{
		free(trimmed_line);
		free(line);
		return (1);
	}
	else if (ft_strlen(trimmed_line) == 1 && *is_map == true)
		exit(printf("Error\nInvalid map\n"));
	else
		*is_map = true;
	free(trimmed_line);
	return (0);
}
