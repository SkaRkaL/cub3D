#include "cub3D.h"
/*
** Auxiliary function to skip white spaces
*/
int is_white_space(char c) {
    return (c == ' ' || c == '\t' || c == '\n');
}
/*
** Iterate through the white spaces at the beginning of the string
*/
int get_first_position(char const *str) {
    int i = 0;
    while (is_white_space(str[i])) {
        i += 1;
    }
    return (i);
}
/*
** Get the length of a string
*/
int get_str_len(char const *str) {
    int len = 0;
    while (str[len] != '\0') {
        len += 1;
    }
    return (len);
}
/*
** Find the last position in a string that is not a white space
*/
int get_last_position(char const *str) {
    int i = get_str_len(str) - 1;
    while (is_white_space(str[i])) {
        i -= 1;
    }
    return (i);
}
/*
** Returns the correct length of a trimmed string
*/
int get_trim_len(char const *str) {
    return (get_last_position(str) - get_first_position(str));
}

char *ft_strtrim(char const *str)
{
    char *trim = NULL;
    int i, len, start, end;
    if (str != NULL) {
        i = 0;
        len = get_trim_len(str) + 1;
        trim = (char *)malloc(len);
        start = get_first_position(str);
        while (i < len) {
            trim[i] = str[start];
            i += 1;
            start += 1;
        }
        trim[i] = '\0';
    }
    return (trim);
}

int	ft_strlcpy(char *dst, char *src, int dstsize)
{
	int	i;
	int	x;

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

char	*ft_substr(char *s, unsigned int start, int len)
{
	char	*str;
	int	i;

	if (!s)
		return (NULL);
	if (!len || start >= ft_strlen(s))
		return (ft_strdup(""));
	i = ft_strlen(s) - start ;
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

char	*gnl(int fd, char **tr)
{
	char	str;
	int		b;
	int		h;

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
	close (fd);
	return (*tr);
}

// " abcde"
int ft_strchr(char *s, int c)
{
	int	i;

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
	map->f = 0;
	map->c = 0;
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

	t_map map = {};
	init_map(&map);

	while (true)
	{
		char *line = get_next_line(fd);
		if (line == NULL)
			break;
		char *trimmed_line = ft_strtrim(line);
		if (ft_strlen(trimmed_line) == 0)
			continue;
		if (number_of_lines < 4) {
			// TODO: parse texture paths
			printf("|%s|\n", trimmed_line);
			char *test = "sjhfjahsfa fadhfjah djafhjhadsh dsajkfhajksdhf";
			char **splitted_line = ft_split(test, ' ');
			for(int i = 0; splitted_line[i] != NULL; i++)
				printf("|%s|\n", splitted_line[i]);
			exit(0);
			printf("|%s|\n", splitted_line[0]);
			puts(splitted_line[0]);
			printf("|%s|\n", splitted_line[1]);
			printf("|%s|\n", splitted_line[2]);
			if (splitted_line == NULL)
				return (ft_putstr_fd("Error\nMalloc error", 2), 1);
			// if (splitted_line[0][0] == 'N' && splitted_line[0][1] == 'O' && splitted_line[0][2] == ' ')
			// 	map.no = ft_substr(splitted_line[3], 0, ft_strlen(splitted_line[3]));
			else 
				return (ft_putstr_fd("Error\nInvalid linee", 2), 1);
		} else if (map_started == false) {
			// TODO: parse colors
		} else {
			// TODO: parse map
		}
		number_of_lines++;
	}
	
	if (number_of_lines == 0)
		return (ft_putstr_fd("Error\nFile is empty", 2), 1);
	if (is_map_valid == false)
		return (ft_putstr_fd("Error\nInvalid Map", 2), 1);
	return (0);
}

