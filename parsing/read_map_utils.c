#include "../cub3D.h"

bool	is_a_member(char c)
{
	return (c == '0' || c == 'W' || c == 'S' || \
				c == 'N' || c == 'E' || c == '1');
}

bool	is_a_player(char c)
{
	return (c == 'W' || c == 'S' || c == 'N' || c == 'E');
}

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
