#include "cub3D.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
	write(fd, "\n", 1);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int		i;
	char	*t1;
	char	*t2;

	i = 0;
	t1 = s1;
	t2 = s2;
	while ((t1[i] || t2[i]) && i < n)
	{
		if (t1[i] > t2[i])
			return (t1[i] - t2[i]);
		else if (t1[i] < t2[i])
			return (t1[i] - t2[i]);
		i++;
	}
	return (0);
}


int	all_ones(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	while (str[i] && str[i] != ' ')
	{
		if (str[i] != '1')
			return (0);
		i++;
	}
	while (str[i] == ' ')
		i++;
	return (1);
}

int	check_line_ones(char *line)
{
	int	tmp_i;

	tmp_i = 0;
	while (line[tmp_i])
	{
		if (line[tmp_i] != '1' || line[tmp_i] != 'N' || line[tmp_i] != '0')
			return (0);
		else
			tmp_i++;
	}
	return (1);
}

int	invalid_number(char *str)
{
	int	i;
	int start_number; 

	i = 0;
	while(str[i] == '0')
		i++;
	start_number = i;
	while (str[i])
	{
		if (*(str + i) < '0' || *(str + i) > '9')
			return (0);
		i++;
	}
	if (i - start_number > 3)
		return (0);
	return (1);
}

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
	return (r << 24 | g << 16 | b << 8 | 1);
}

int	check_commas(char *str)
{
	int	i;
	int	commas;

	i = 0;
	commas = 0;
	while (str[i])
	{
		if (str[i] == ',')
			commas++;
		i++;
	}
	if (commas != 2)
		return (1);
	return (0);
}

bool	is_a_member(char c)
{
	return (c == '0' || c == 'W' || c == 'S' || \
				c == 'N' || c == 'E' || c == '1');
}

bool	is_a_player(char c)
{
	return (c == 'W' || c == 'S' || c == 'N' || c == 'E');
}

char	*ft_repeat(char c, size_t a)
{
	int		i;
	char	*s;

	s = malloc((a + 1) * sizeof(char));
	if (!s)
		return (NULL);
	i = 0;
	while (i < a)
	{
		s[i] = c;
		i++;
	}
	s[a] = '\0';
	return (s);
}

void	*ft_memset(void *b, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		*((char *)b + i++) = c;
	return (b);
}

void	check_args(int ac, char **av)
{
	if (ac != 2)
	{
		ft_putstr_fd("Error\nWrong number of arguments", 2);
		exit(1);
	}
	if (ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 4) || ft_strlen(av[1]) <= 5)
	{
		ft_putstr_fd("Error\nCan't open file", 2);
		exit(1);
	}
}

void	exit_err(char *str)
{
	ft_putstr_fd(str, 2);
	exit(1);
}

void	insert_colors(char *path, t_map *map, int i)
{
	char	**color;
	int		rgb;

	if (check_commas(path))
		exit_err("Error\nInvalid color");
	color = ft_split(path, ',');
	rgb = set_color(color);
	if (rgb == 1)
		exit_err("Error\nInvalid color");
	*((int *)&map->c + (i - 4)) = rgb;
	check_isfree(color);
	color = NULL;
}

void	check_textures_colors(char *trimmed_line, short *flag, t_map *map)
{
	static char		*kk[6] = {"NO", "SO", "WE", "EA", "C", "F"};
	static short	kk_flag[6] = {1, 2, 4, 8, 16, 32};
	int				i;
	char			*dir;
	char			*path;

	dir = ft_strtok(trimmed_line, " ");
	path = ft_strtok(NULL, "");
	if (path == NULL)
		exit_err("Error\nInvalid path");
	i = -1;
	while (++i < 6)
		if (!ft_strncmp(dir, kk[i], ft_strlen(kk[i])))
		{
			if (*flag & kk_flag[i])
				exit_err("Error\nDuplicate key");
			*flag |= kk_flag[i];
			if (i < 4)
				*((char **)&map->no + i) = ft_strdup(path);
			else
				insert_colors(path, map, i);
		}
	free(path);
	free(dir);
}

void	check_duplicates(short flag, short full_flag)
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
		exit_err("Error\nMissing key");
	}
}

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
		return 1 ;
	}
	else if (ft_strlen(trimmed_line) == 1 && *is_map == true)
		exit(printf("Error\nInvalid map\n"));
	else
		*is_map = true;
	free(trimmed_line);
	return 0;
}

void	read_map(int fd, t_map *map)
{
	char	*line;
	char	*trimmed_line;
	char	*tmp;
	bool	is_map; 

	is_map = false;
	tmp = ft_strdup("");
	while(true)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (empty_line(line, map, &is_map)) continue;
		tmp = ft_strjoin(tmp, line);
		map->height++;
	}
	map->map = ft_split(tmp, '\n');
	if (map->map == NULL)
		exit(printf("Error\nInvalid map\n"));
	free(tmp);
}

void	fill_map(t_map *map)
{
	char	*spaces;
	int		i;

	i = 0;
	while (i < map->height)
	{
		int line_length = ft_strlen(map->map[i]);
		if (line_length < map->width)
		{
			spaces = ft_repeat(' ', map->width - line_length);
			map->map[i] = ft_strjoin(map->map[i], spaces);
		}
		i++;
	}
}

void	read_file_content(int fd, t_map *map)
{
	read_textures(fd, map);
	read_map(fd, map);
	fill_map(map);
}

void	check_in_border(int i, int j, t_map *map)
{
	if (is_a_member(map->map[i][j]) && map->map[i][j] != '1')
	{
		// empty or playerP 
		if (j == 0 || map->map[i][j + 1] ==  '\0')
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

int main(int ac, char **av)
{
	int		fd;
	t_map	map;

	check_args(ac, av);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (ft_putstr_fd("Error\nFile not found", 2), 1);

	// Read file content

	ft_memset(&map, 0, sizeof(t_map));
	read_file_content(fd, &map);
	
	check_map_errors(&map);

	for(int i = 0; i < map.height; i++)
	{
		printf("|%s|\n", map.map[i]);
	}
	puts("\n--------- Map ---------");
	printf("C. %u, F. %u\n", map.c.value, map.f.value);
	printf("NO : %s\n", map.no);
	printf("SO : %s\n", map.so);
	printf("WE : %s\n", map.we);
	printf("EA : %s\n", map.ea);
	
	puts("\n--------- Floor ---------");
	printf("COLOR ======>	: %#x\n",	map.f.value);
	printf("COLOR => Red	: %d\n", map.f.r);
	printf("COLOR => Green	: %d\n", map.f.g);
	printf("COLOR => Blue	: %d\n", map.f.b);
	printf("COLOR => Alpha	: %d\n", map.f.a);

	puts("\n--------- Ceiling ---------");
	printf("COLOR ======>	: %#x\n",	map.c.value);
	printf("COLOR => Red	: %d\n", map.c.r);
	printf("COLOR => Green	: %d\n", map.c.g);
	printf("COLOR => Blue	: %d\n", map.c.b);
	printf("COLOR => Alpha	: %d\n", map.c.a);

	puts("\n--------- HEIGHT ---------");
	printf("HEIGHT	: %d\n", map.height);
	puts("\n--------- WIDTH ---------");
	printf("WIDTH	: %d\n", map.width);
	// free(map.no);
	// free(map.so);
	// free(map.we);
	// free(map.ea);
	// while (1);
	close(fd);
	return (0);
}
