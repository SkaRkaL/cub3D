#include "cub3D.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	signe;
	int	resu;

	i = 0;
	signe = 1;
	resu = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		resu = resu * 10 + (str[i] - 48);
		i++;
	}
	return (resu * signe);
}

int is_white_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int get_first_position(char *str)
{
	int i = 0;
	if (str == NULL)
		return (0);
	while (is_white_space(str[i]))
	{
		i += 1;
	}
	return (i);
}

int get_str_len(char *str)
{
	int len = 0;
	if (str == NULL)
		return (0);
	while (str[len] != '\0')
	{
		len += 1;
	}
	return (len);
}

int get_last_position(char *str)
{
	if (str == NULL)
		return (0);
	int i = get_str_len(str);
	printf("i = %d\n", i);
	while (str[i] && is_white_space(str[i]))
	{
		i -= 1;
	}
	return (i);
}

int get_trim_len(char *str)
{
	if (str == NULL)
		return (0);
	return (get_last_position(str) - get_first_position(str));
}

char	*ft_strtrim(char const *s, char const *set)
{
	int		strt;
	int		end;
	char	*ptr;

	strt = 0;
	if (s == NULL)
		return (NULL);
	if (s[0] == '\0')
		return (strdup(""));
	if (set == NULL)
		return (strdup(s));
	while (strchr(set, s[strt]) && s[strt])
		strt++;
	end = strlen(s);
	while (strchr(set, s[end]) && end != 0)
		end--;
	if (end < strt)
		return (strdup(""));
	ptr = ft_substr(s, strt, end - strt + 1);
	return (ptr);
}

int ft_strlcpy(char *dst, char *src, int dstsize)
{
	int i;
	int x;

	x = ft_strlen(src);
	i = 0;
	if (dstsize != 0)
	{
		while (src[i] && i < dstsize - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = 0;
	}
	return (x);
}

char *ft_strtok(char *str, char *sep)
{
	static char *remainder;
	char *ret;
	int len;

	if (str)
		remainder = str;
	if (!remainder)
		return (NULL);
	while (*remainder && strchr(sep, *remainder))
		remainder++;
	len = 0;
	while (remainder[len] && !strchr(sep, remainder[len]))
		len++;
	if (!len)
		return (NULL);
	ret = ft_substr(remainder, 0, len);
	remainder += len;
	while (*remainder && strchr(sep, *remainder))
		remainder++;
	return (ret);
}

char *ft_substr(char const *s, unsigned int start, int len)
{
	char *str;
	int i;

	if (!s)
		return (NULL);
	if (!len || start >= strlen(s))
		return (ft_strdup(""));
	i = strlen(s) - start;
	if (i > len)
		i = len;
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (0);
	strlcpy(str, s + start, i + 1);
	return (str);
}

void ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void ft_putstr_fd(char *s, int fd)
{
	int i;

	i = 0;
	if (!s)
		return;
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
	write(fd, "\n", 1);
}

int ft_strncmp(char *s1, char *s2, int n)
{
	int i;
	char *t1;
	char *t2;

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

char *gnl(int fd, char **tr)
{
	char str;
	int b;
	int h;

	b = 1;
	h = 0;
	while (b != 0)
	{
		b = read(fd, &str, 1);
		if (b == -1)
			return (0);
		if (b != 0)
			*tr[h++] = str;
		*tr[h] = '\0';
	}
	if (h == 0)
		return (0);
	close(fd);
	return (*tr);
}

int ft_strchr(char *s, int c)
{
	int i;

	i = -1;
	while (s[++i])
		if (s[i] == c)
			return (i);
	return (-1);
}

void init_map(t_map *map)
{
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

int all_ones(char *str)
{
	int i;

	i = 0;
	while (str[i] == ' ')
		i++;

	while (str[i] && str[i] != ' ')
	{
		if (str[i] != '1')
			return (0);
		i++;
	}
	return (1);
}

int all_one(char *str, bool *is_map)
{
	int i;

	i = 0;
	while (str[i] == ' ')
		i++;

	if (str[i] == '1')
	{
		*is_map = true;
		i++;
		while (str[i] && str[i] != ' ')
		{
			if (str[i] != '1')
				return (0);
			i++;
		}
	}
	return (1);
}

int check_line_ones(char *line)
{
	int tmp_i;

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

int check_line_is_empty(char *line)
{
	int i = 0;
	while (line[i] != '\n')
	{
		if (line[i] != ' ' || line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

int ft_isdigit(char *str)
{
	int i = 0;
	while (str[i])
	{
		if (*(str + i) < '0' || *(str + i) > '9')
			return (0);
		i++;
	}
	return (1);
}

int set_color(char **color)
{
	// size of color must be 3
	int i = 0;
	while(color[i])
	{
		if (!ft_isdigit(color[i]))
			return (1);
		i++;
	}
	if (i != 3)
		return (1);
	if (ft_atoi(color[0]) > 255 || ft_atoi(color[1]) > 255 || ft_atoi(color[2]) > 255)
		return (1);
	if (ft_atoi(color[0]) < 0 || ft_atoi(color[1]) < 0 || ft_atoi(color[2]) < 0)
		return (1);
	return (bound(ft_atoi(color[0])) << 24 | bound(ft_atoi(color[1])) << 16 | bound(ft_atoi(color[2])) << 8 | 1);
}

int check_commas(char *str)
{
	int i = 0;
	int commas = 0;
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

int is_not_empty(char *str)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] != ' ' || str[i] != '\t' || str[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

bool	is_a_mamber(char c)
{
	return (c == '0' || c == 'W' || c == 'S' || c == 'N' || c == 'E' || c == '1');
}

bool	is_a_player(char c)
{
	return (c == 'W' || c == 'S' || c == 'N' || c == 'E');
}

char *ft_repeat(char c, size_t a)
{
    char *s = malloc((a + 1) * sizeof(char));
	if (!s)
		return (NULL);
    for (int i = 0; i < a; i++)
        s[i] = c;
	s[a] = '\0';
    return (s);
}

int main(int ac, char **av)
{
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\\/
	if (ac != 2)
		return (ft_putstr_fd("Error\nWrong number of arguments", 2), 1);
	if (ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 4))
		return (ft_putstr_fd("Error\nWrong file extension", 2), 1);
	if (ft_strlen(av[1]) < 5)
		return (ft_putstr_fd("Error\nWrong file extension", 2), 1);
	if (ft_strlen(av[1]) == 5)
		return (ft_putstr_fd("Error\nWrong file extension", 2), 1);
	int fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (ft_putstr_fd("Error\nFile not found", 2), 1);
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\\/

	// Read file content

	int number_of_lines = 0;

	t_map map;
	init_map(&map);
	char *dir;
	char *line;
	char *path;
	short flag = 0;
	short full_flag = 1 | 2 | 4 | 8 | 16 | 32;
	static char *kk[6] = {"NO", "SO", "WE", "EA", "C", "F"};
	static short kk_flag[6] = {1, 2, 4, 8, 16, 32};
	int map_index = 0;
	while (flag != full_flag)
	{
		line = get_next_line(fd);
		if (line == NULL || all_ones(line))
			break ;
		char *trimmed_line = ft_strtrim(line, "\n \t");

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
	bool is_map = false;
	char *trimmed_line;
	int largest_line_length = 0;
	while(true)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		int line_length = ft_strlen(line);
		if (line[line_length - 1] == '\n')
			line_length--;
		if (line_length > largest_line_length)
				largest_line_length = line_length;
		trimmed_line = ft_strtrim(line, "\t ");
		if (ft_strlen(trimmed_line) == 1)
		{
			free(trimmed_line);
			continue ;
		}
		free(trimmed_line);
		tmp = ft_strjoin(tmp, line);
		number_of_lines++;
	}
	map.map = ft_split(tmp, '\n');
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
	printf("max length = %d\n", largest_line_length);

	i = 0;
	char *spaces;
	while (i < number_of_lines - 6)
	{
		int line_length = ft_strlen(map.map[i]);
		if (line_length < largest_line_length)
		{
			spaces = ft_repeat(' ', largest_line_length - line_length);
			char *temp = map.map[i];
			map.map[i] = ft_strjoin(temp, spaces);
			free(temp);
			free(spaces);
		}
		i++;
	}

	for (int i  = 0; i < number_of_lines - 6; i++)
	{
		for (int j = 0; map.map[i][j]; j++)
		{
			if (is_a_player(map.map[i][j]))
			{
				if (map.x != 0)
					exit(printf("Zaaaabi\n"));
				map.x = j;
				map.y = i;
			}
			if (!(is_a_mamber(map.map[i][j]) || map.map[i][j] == ' '))
				exit(printf("Non valid elemnt!\n"));
			if (is_a_mamber(map.map[i][j]) && map.map[i][j] != '1')
			{
				if (j == 0 || map.map[i][j + 1] ==  '\0')
					exit(printf("l9lawi\n"));
				if (i == 0 || i == number_of_lines - 5)
					exit(printf("l9lawi again\n"));
				if (!is_a_mamber(map.map[i][j + 1]))
					exit(printf("l9lawi again\n"));
				if (!is_a_mamber(map.map[i][j - 1]))
					exit(printf("l9lawi again\n"));
				if (!is_a_mamber(map.map[i + 1][j]))
					exit(printf("l9lawi again\n"));
				if (!is_a_mamber(map.map[i - 1][j]))
					exit(printf("l9lawi again\n"));
			}
		}
	}

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

	return (0);
}
