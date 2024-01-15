#include "../cub3D.h"

void	clear_exit(t_game *game, int exit_status)
{
	int	i;

	i = 0;
	while (i < game->height / TILE)
		free(game->map[i++]);
	free(game->map);
	if (game->no_texture)
		mlx_delete_texture(game->no_texture);
	if (game->so_texture)
		mlx_delete_texture(game->so_texture);
	if (game->ea_texture)
		mlx_delete_texture(game->ea_texture);
	if (game->we_texture)
		mlx_delete_texture(game->we_texture);
	if (game->img)
		mlx_delete_image(game->mlx, game->img);
	if (game->mlx)
		mlx_terminate(game->mlx);
	exit(exit_status);
}

void	initalize_textures(t_game *game, t_map *map)
{
	game->no_texture = mlx_load_png(map->no);
	game->ea_texture = mlx_load_png(map->ea);
	game->so_texture = mlx_load_png(map->so);
	game->we_texture = mlx_load_png(map->we);
	free(map->no);
	free(map->ea);
	free(map->so);
	free(map->we);
	if (!game->no_texture || !game->so_texture
		|| !game->we_texture || !game->ea_texture)
	{
		ft_putstr_fd("Error : Can't read texture file\n", 2);
		clear_exit(game, EXIT_FAILURE);
	}
}

void	intialize_game_vars(t_game *game, t_map *map)
{
	game->map = map->map;
	game->width = map->width * TILE;
	game->height = map->height * TILE;
	game->ply.x = map->x * TILE + TILE / 2;
	game->ply.y = map->y * TILE + TILE / 2;
	game->floor_color = map->f.value;
	game->ceil_color = map->c.value;
	if (map->orientation == 'N')
		game->ply.angle = -M_PI / 2;
	else if (map->orientation == 'S')
		game->ply.angle = M_PI / 2;
	else if (map->orientation == 'E')
		game->ply.angle = 0;
	else
		game->ply.angle = M_PI;
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", 0);
	if (!game->mlx)
		clear_exit(game, EXIT_FAILURE);
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
		clear_exit(game, EXIT_FAILURE);
	initalize_textures(game, map);
}

void	graphic_handle(t_map *map)
{
	t_game	game;

	memset(&game, 0, sizeof(game));
	intialize_game_vars(&game, map);
	mlx_image_to_window(game.mlx, game.img, 0, 0);
	mlx_loop_hook(game.mlx, hook_handle, &game);
	mlx_loop(game.mlx);
	clear_exit(&game, EXIT_SUCCESS);
}
