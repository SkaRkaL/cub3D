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

int	bound(int c)
{
	if (c < 0)
		return (0);
	if (c > 255)
		return (255);
	return ((int)c);
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

void	*ft_memset(void *b, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		*((char *)b + i++) = c;
	return (b);
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
	short			full_flag;
	int				number_of_lines;
	char			*dir;
	char			*line;
	char			*path;
	char			*trimmed_line;
	bool			is_map;

	is_map = false;
	flag = 0;
	number_of_lines = 0;
	full_flag = 1 | 2 | 4 | 8 | 16 | 32;
	ft_memset(&map, 0, sizeof(t_map));
	char **color = NULL;
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
		dir = ft_strtok(trimmed_line, " ");
		path = ft_strtok(NULL, "");
		if (path == NULL)
			return (ft_putstr_fd("Error\nInvalid path", 2), 1);
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
					*((char **)&map.no + i) = ft_strdup(path);
				}
				else
				{
					if (check_commas(path))
						return (printf("ERROR\nINVALID COLOR"), 1);
					color = ft_split(path, ',');
					int rgb = set_color(color);
					if (rgb == 1)
						return (ft_putstr_fd("Error\nInvalid color", 2), 1);
					*((int *)&map.c + (i - 4)) = rgb;
					check_isfree(color);
					color = NULL;
				}
				free(path);
			}
			i++;
		}
		number_of_lines++;
		free(trimmed_line);
		free(line);
		free(dir);

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
			free(line);
			continue ;
		}
		else if (ft_strlen(trimmed_line) == 1 && is_map == true)
		{
			exit(printf("Error\nInvalid map\n"));
		}
		else
			is_map = true;
		free(trimmed_line);
		tmp = ft_strjoin(tmp, line);
		map.height++;
	}
	map.map = ft_split(tmp, '\n');
	if (map.map == NULL)
		exit(printf("Error\nInvalid map\n"));
	free(tmp);

	int i = 0;
	char *spaces;
	while (i < map.height)
	{
		int line_length = ft_strlen(map.map[i]);
		if (line_length < map.width)
		{
			spaces = ft_repeat(' ', map.width - line_length);
			map.map[i] = ft_strjoin(map.map[i], spaces);
		}
		i++;
	}


	for (int i  = 0; i < map.height; i++)
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
				if (i == 0 || i == map.height - 1)
					exit(printf("Error again 1\n"));
				if (!is_a_mamber(map.map[i][j + 1]))
					exit(printf("Error again 2\n"));
				if (!is_a_mamber(map.map[i][j - 1]))
					exit(printf("Error again 3\n"));
				if (!is_a_mamber(map.map[i + 1][j]))
					exit(printf("Error again 4\n"));
				if (!is_a_mamber(map.map[i - 1][j]))
					exit(printf("Error again 5\n"));
			}
		}
	}

	if (!map.x)
		exit(puts("No Player in your map"));

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
	return (0);
}
