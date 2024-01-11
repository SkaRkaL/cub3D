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

void	init_map(t_map *map)
{
	map->height = 0;
	map->width = 0;
	map->x = 0;
	map->y = 0;
	map->map = NULL;
	map->no = NULL;
	map->so = NULL;
	map->we = NULL;
	map->ea = NULL;
	map->f.value = 0;
	map->c.value = 0;
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

int	bound(int c)
{
	if (c < 0)
		return (0);
	if (c > 255)
		return (255);
	return ((int)c);
}

int	ft_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (*(str + i) < '0' || *(str + i) > '9')
			return (0);
		i++;
	}
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
		if (!ft_isdigit(color[i]))
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
	return (bound(r) << 24 | bound(g) << 16 | bound(b) << 8 | 1);
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

bool	is_a_mamber(char c)
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

int main(int ac, char **av)
{
	int	fd;

	if (ac != 2)
		return (ft_putstr_fd("Error\nWrong number of arguments", 2), 1);
	if (ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 4))
		return (ft_putstr_fd("Error\nWrong file extension", 2), 1);
	if (ft_strlen(av[1]) < 5)
		return (ft_putstr_fd("Error\nWrong file extension", 2), 1);
	if (ft_strlen(av[1]) == 5)
		return (ft_putstr_fd("Error\nWrong file extension", 2), 1);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (ft_putstr_fd("Error\nFile not found", 2), 1);

	// Read file content

	t_map			map;
	static char		*kk[6] = {"NO", "SO", "WE", "EA", "C", "F"};
	static short	kk_flag[6] = {1, 2, 4, 8, 16, 32};
	short			flag;
	int				map_index;
	short			full_flag;
	int				number_of_lines;
	char			*dir;
	char			*line;
	char			*path;
	char			*trimmed_line;
	bool			is_map;

	is_map = false;
	flag = 0;
	map_index = 0;
	number_of_lines = 0;
	full_flag = 1 | 2 | 4 | 8 | 16 | 32;
	init_map(&map);
	while (flag != full_flag)
	{
		line = get_next_line(fd);
		if (line == NULL || all_ones(line))
			break ;
		trimmed_line = ft_strtrim(line, "\n \t");
		if (!trimmed_line || ft_strlen(trimmed_line) == 0)
			continue;
		if (!check_line_ones(trimmed_line))
		{
			dir = ft_strtok(trimmed_line, " ");
			path = ft_strtok(NULL, "");
			int i = 0;
			while (i < 6)
			{
				if (!ft_strncmp(dir, kk[i], ft_strlen(kk[i])))
				{
					if (flag & kk_flag[i])
						return (ft_putstr_fd("Error\nDuplicate key", 2), 1);
					flag |= kk_flag[i];

					if (i < 4)
					{
						if (path == NULL)
							return (ft_putstr_fd("Error\nInvalid path", 2), 1);
						*((char **)&map.no + i) = ft_strdup(path);
					}
					else
					{
						if (path == NULL)
							return (ft_putstr_fd("Error\nInvalid path", 2), 1);
						if (check_commas(path))
							return (1);
						char **color = ft_split(path, ',');
						int rgb = set_color(color);
						if (rgb == 1)
							return (ft_putstr_fd("Error\nInvalid color", 2), 1);
						*((int *)&map.c + (i - 4)) = rgb;
					}
				}
				i++;
			}
		}

		number_of_lines++;
	}
	if (number_of_lines == 0)
		return (ft_putstr_fd("Error\nFile is empty", 2), 1);
	if (flag != full_flag)
	{
		int i = 0;
		while (i < 6)
		{
			if (!(flag & kk_flag[i]))
				printf("missing [ %s ] key \n", kk[i]);
			i++;
		}
		return (ft_putstr_fd("Error\nMissing key", 2), 1);
	}
	char *tmp = ft_strdup("");
	free(trimmed_line);
	trimmed_line = NULL;
	map.width = 0;
	while(true)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		int line_length = ft_strlen(line);
		if (line[line_length - 1] == '\n')
			line_length--;
		if (line_length > map.width)
				map.width = line_length;
		trimmed_line = ft_strtrim(line, "\t ");
		if (ft_strlen(trimmed_line) == 1 && is_map == false)
		{
			free(trimmed_line);
			continue ;
		}
		else
			is_map = true;
		free(trimmed_line);
		tmp = ft_strjoin(tmp, line);
		number_of_lines++;
	}
	map.map = ft_split(tmp, '\n');
	for (int index = 0; tmp[index]; index++)
		if (tmp[index] == '\n' && tmp[index + 1] && tmp[index + 1] == '\n')
			exit(printf("Error\nInvalid map\n"));
	int i;
	int opn;
	i = 0;
	while (i < 4)
	{
		if (ft_strncmp(*((char **)&map.no + i) + ft_strlen(*((char **)&map.no + i)) - 4, ".xpm", 4) || !(flag & kk_flag[i]))
			return (printf("Error\nMissing [ %s ] Texture file \n", kk[i]), 1);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		opn = open(*((char **)&map.no + i), O_RDONLY);
		if (opn == -1 || !(flag & kk_flag[i]))
			return (printf("Error\nMissing [ %s ] Invalid path \n", kk[i]), 1);
		i++;
	}

	i = 0;
	char *spaces;
	while (i < number_of_lines - 6)
	{
		int line_length = ft_strlen(map.map[i]);
		if (line_length < map.width)
		{
			spaces = ft_repeat(' ', map.width - line_length);
			char *temp = map.map[i];
			map.map[i] = ft_strjoin(temp, spaces);
			free(temp);
			free(spaces);
		}
		i++;
	}

	int height = 0;
	for (int i  = 0; i < number_of_lines - 6; i++)
	{
		for (int j = 0; map.map[i][j]; j++)
		{
			if (is_a_player(map.map[i][j]))
			{
				if (map.x != 0)
					exit(printf("ERROOOORRRR\n"));
				map.x = j;
				map.y = i;
			}
			if (!(is_a_mamber(map.map[i][j]) || map.map[i][j] == ' '))
				exit(printf("Non valid elemnt!\n"));
			if (is_a_mamber(map.map[i][j]) && map.map[i][j] != '1')
			{
				if (j == 0 || map.map[i][j + 1] ==  '\0')
					exit(printf("Error\n"));
				if (i == 0 || i == number_of_lines - 5)
					exit(printf("Error again\n"));
				if (!is_a_mamber(map.map[i][j + 1]))
					exit(printf("Error again\n"));
				if (!is_a_mamber(map.map[i][j - 1]))
					exit(printf("Error again\n"));
				if (!is_a_mamber(map.map[i + 1][j]))
					exit(printf("Error again\n"));
				if (!is_a_mamber(map.map[i - 1][j]))
					exit(printf("Error again\n"));
				// if line only spaces or len == 1
			}
		}
		height = i;
	}
	map.width = map.width;
	map.height = height;

	if (!map.x)
		exit(puts("No Player in your map"));

	for(int i = 0; i < number_of_lines - 6; i++)
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
	return (0);
}
