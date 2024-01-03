#include "cub3D.h"

int is_white_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int get_first_position(char const *str)
{
	int i = 0;
	while (is_white_space(str[i]))
	{
		i += 1;
	}
	return (i);
}

int get_str_len(char const *str)
{
	int len = 0;
	while (str[len] != '\0')
	{
		len += 1;
	}
	return (len);
}

int get_last_position(char const *str)
{
	int i = get_str_len(str) - 1;
	while (is_white_space(str[i]))
	{
		i -= 1;
	}
	return (i);
}

int get_trim_len(char const *str)
{
	return (get_last_position(str) - get_first_position(str));
}

char *ft_strtrim(char const *str)
{
	if (str == NULL)
		return (NULL);

	char *trim = NULL;
	int i, len, start, end;
	i = 0;
	len = get_trim_len(str);
	trim = (char *)malloc(len + 1);
	if (trim == NULL)
		return (NULL);
	start = get_first_position(str);
	while (i <= len)
	{
		trim[i] = str[start];
		i += 1;
		start += 1;
	}
	trim[i] = '\0';
	return (trim);
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

char *ft_substr(char *s, unsigned int start, int len)
{
	char *str;
	int i;

	if (!s)
		return (NULL);
	if (!len || start >= ft_strlen(s))
		return (ft_strdup(""));
	i = ft_strlen(s) - start;
	if (i > len)
		i = len;
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (0);
	ft_strlcpy(str, s + start, i + 1);
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

// " abcde"
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

int check_line_ones(char *line)
{
	int tmp_i;

	tmp_i = 0;
	while (line[tmp_i])
	{
		if (line[tmp_i] != '1')
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

int main(int ac, char **av)
{
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\\/
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
	bool map_started = false;
	bool is_map_valid = true;

	t_map map;
	init_map(&map);

	char *dir;
	char *line;
	char *path;
	short flag = 0;
	short full_flag = 1 | 2 | 4 | 8 | 16 | 32;
	static char *kk[6] = {"NO", "SO", "WE", "EA", "F", "C"};
	static short kk_flag[6] = {1, 2, 4, 8, 16, 32};
	while (true && flag != full_flag)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break;
		char *trimmed_line = ft_strtrim(line);

		if (!trimmed_line || ft_strlen(trimmed_line) == 0)
			continue;
		if (!check_line_ones(trimmed_line))
		{

			printf("	[ %s ]\n", trimmed_line);
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
						char **color = ft_split(path, ',');
						*((int *)&map.f + (i - 4)) = (bound(atoi(color[0])) << 24 | bound(atoi(color[1])) << 16 | bound(atoi(color[2])) << 8 | 1);
					}
				}
				i++;
			}
		}

		number_of_lines++;
	}
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

	printf("C. %u, F. %u\n", map.c.value, map.f.value);
	printf("no: %s\n", map.no);
	printf("so: %s\n", map.so);
	printf("we: %s\n", map.we);
	printf("ea: %s\n", map.ea);
	
	puts("\n--------- F ---------");
	printf("color: %X\n", map.f.value);
	printf("color r: %d\n", map.f.r);
	printf("color g: %d\n", map.f.g);
	printf("color b: %d\n", map.f.b);
	printf("color a: %d\n", map.f.a);
	puts("--------- C ---------");
	printf("color: %X\n", map.c.value);
	printf("color r: %d\n", map.c.r);
	printf("color g: %d\n", map.c.g);
	printf("color b: %d\n", map.c.b);
	printf("color a: %d\n", map.c.a);

	if (number_of_lines == 0)
		return (ft_putstr_fd("Error\nFile is empty", 2), 1);
	if (is_map_valid == false)
		return (ft_putstr_fd("Error\nInvalid Map", 2), 1);
	return (0);
}
