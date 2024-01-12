#include "cub3D.h"

void	check_args(int ac, char **av)
{
	if (ac != 2)
		exit_err("Error\nInvalid number of arguments");
	if (ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 4) \
		|| ft_strlen(av[1]) <= 5)
		exit_err("Error\nInvalid file");
}

void	read_file_content(int fd, t_map *map)
{
	read_textures(fd, map);
	read_map(fd, map);
	fill_map(map);
}

int	main(int ac, char **av)
{
	int		fd;
	int		i;
	t_map	map;

	check_args(ac, av);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (ft_putstr_fd("Error\nFile not found", 2), 1);
	ft_memset(&map, 0, sizeof(t_map));
	read_file_content(fd, &map);
	check_map_errors(&map);
	i = 0;
	while (i < map.height)
	{
		printf("|%s|\n", map.map[i++]);
	}
	puts("\n--------- Map ---------");
	printf("C. %u, F. %u\n", map.c.value, map.f.value);
	printf("NO : %s\n", map.no);
	printf("SO : %s\n", map.so);
	printf("WE : %s\n", map.we);
	printf("EA : %s\n", map.ea);
	puts("\n--------- Floor ---------");
	printf("COLOR ======>	: %#x\n", map.f.value);
	printf("COLOR => Red	: %d\n", map.f.r);
	printf("COLOR => Green	: %d\n", map.f.g);
	printf("COLOR => Blue	: %d\n", map.f.b);
	printf("COLOR => Alpha	: %d\n", map.f.a);
	puts("\n--------- Ceiling ---------");
	printf("COLOR ======>	: %#x\n", map.c.value);
	printf("COLOR => Red	: %d\n", map.c.r);
	printf("COLOR => Green	: %d\n", map.c.g);
	printf("COLOR => Blue	: %d\n", map.c.b);
	printf("COLOR => Alpha	: %d\n", map.c.a);
	puts("\n--------- HEIGHT ---------");
	printf("HEIGHT	: %d\n", map.height);
	puts("\n--------- WIDTH ---------");
	printf("WIDTH	: %d\n", map.width);
	close(fd);
	return (0);
}
