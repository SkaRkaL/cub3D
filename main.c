/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asettar <asettar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:53:18 by asettar           #+#    #+#             */
/*   Updated: 2024/01/15 20:18:13 by asettar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	exit_err(char *str, t_map *map)
{
	int	i;

	ft_putstr_fd(str, 2);
	if (map)
		close(map->fd);
	if (!map)
		exit(1);
	if (map->no)
		free(map->no);
	if (map->so)
		free(map->so);
	if (map->we)
		free(map->we);
	if (map->ea)
		free(map->ea);
	if (map->map)
	{
		i = 0;
		while (map->map[i])
			free(map->map[i++]);
		free(map->map);
	}
	exit(1);
}

void	check_args(int ac, char **av)
{
	if (ac != 2)
		exit_err("Error\nInvalid number of arguments", NULL);
	if (ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 4) \
		|| ft_strlen(av[1]) <= 5)
		exit_err("Error\nInvalid file", NULL);
}

void	read_file_content(t_map *map)
{
	read_textures(map);
	read_map(map);
}

// void	leaks(void)
// {
// 	char	s[1000];
// 	sprintf(s, "%d", getpid());
// 	system(ft_strjoin(strdup("lsof -p "), strdup(s)));
// 	system("leaks cub3D");
// }

int	main(int ac, char **av)
{
	t_map	map;

	check_args(ac, av);
	ft_memset(&map, 0, sizeof(t_map));
	map.fd = open(av[1], O_RDONLY);
	if (map.fd == -1)
		return (ft_putstr_fd("Error\nFile not found", 2), 1);
	read_file_content(&map);
	close(map.fd);
	graphic_handle(&map);
	return (0);
}
