#include "../cub3D.h"

void	draw_rectangle(t_game *game, int y, int x, int color)
{
	for(int j = 0; j <  TILE; j++){
		for(int i = 0; i < TILE; i++){
			mlx_put_pixel(game->img, x + i, y + j, color);
		}
	}
}
void draw_line(t_game *game) {
	double start_x = game->ply.x;
	double start_y = game->ply.y;
	int x = 0;
	while (x < 20) {
		start_x += cos(game->ply.angle);
		start_y += sin(game->ply.angle);
		mlx_put_pixel(game->img, start_x, start_y, 0xFF0000FF);
		x++;
	}
}

void	draw_point(t_game *game, double x, double y)
{
	mlx_put_pixel(game->img, x, y, 0xFF0000FF);
	mlx_put_pixel(game->img, x + 1, y, 0xFF0000FF);
	mlx_put_pixel(game->img, x - 1, y, 0xFF0000FF);
	mlx_put_pixel(game->img, x, y + 1, 0xFF0000FF);
	mlx_put_pixel(game->img, x, y - 1, 0xFF0000FF);
	mlx_put_pixel(game->img, x + 2, y, 0xFF0000FF);
	mlx_put_pixel(game->img, x - 2, y, 0xFF0000FF);
	mlx_put_pixel(game->img, x, y + 2, 0xFF0000FF);
	mlx_put_pixel(game->img, x, y - 2, 0xFF0000FF);
}
void	draw_map(t_game *game)
{
	for(int y = 0; game->map[y] != NULL; y++){
		for(int x = 0; game->map[y][x] != 0; x++){
			// printf("x: %d, y: %d\n", x, y);
			if (ft_strchr("NSEW0", game->map[y][x]))
				draw_rectangle(game, y * TILE, x * TILE, 0xFFFFFFFF);
			else 
				draw_rectangle(game, y * TILE, x * TILE, 0x000ccccc);
		}
	}
	draw_point(game, game->ply.x, game->ply.y);
	draw_line(game);
}
