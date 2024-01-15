#include "../cub3D.h"

void horizantal_intersection(t_game *game, t_ray *ray)
{
	// double distance = 0.0;
	double xinter, yinter;
	yinter = floor(game->ply.y / TILE) * TILE;
	if (sin(ray->angle) > 0) yinter += TILE;
	else yinter -= 0.0000001;
	xinter = (yinter - game->ply.y) / tan(ray->angle) + game->ply.x;
	// draw_point(game, xinter, yinter);
	// printf("%f : %f   ||  ", game->ply.y, game->ply.x);
	// printf("%f : %f\n", yinter, xinter);

	double ystep = TILE;
	if (sin(ray->angle) < 0)
		ystep *= -1;
	double xstep = ystep / tan(ray->angle);
	// printf("%f : %f\n", yinter, xinter);
	while (1)
	{
		if (xinter <= 0 || xinter >= game->width || yinter <= 0 || yinter >= game->height)
			break;
		// printf("%f : %f\n", yinter, xinter);

		if (game->map[(int)((yinter)/ TILE)][(int)(xinter / TILE)] == '1'){
			// printf("%f : %f || \n", yinter, xinter);
			ray->wall_hitx = xinter;
			ray->wall_hity = yinter;
			ray->horizantal_intersection = 1;
			ray->distance_to_wall = sqrt(pow(xinter - game->ply.x, 2) + pow(yinter - game->ply.y, 2));
			// draw_point(game, ray->wall_hitx, ray->wall_hity);
			return ;
		}
		xinter += xstep;
		yinter += ystep;
	}
	ray->distance_to_wall = INT_MAX;
}

void vertical_intersection(t_game *game, t_ray *ray)
{
	double xinter, yinter;
	xinter = floor(game->ply.x / TILE) * TILE;
	if (cos(ray->angle) > 0) xinter += TILE;
	else xinter -= 0.0000001;
	yinter = (xinter - game->ply.x) * tan(ray->angle) + game->ply.y;

	// draw_point(game, xinter, yinter);
	// printf("%f : %f   ||  ", game->ply.y, game->ply.x);
	// printf("%f : %f\n", yinter, xinter);

	double xstep = TILE;
	if (cos(ray->angle) < 0)
		xstep *= -1;
	double ystep = xstep * tan(ray->angle);
	// printf("%f : %f\n", yinter, xinter);
	while (1)
	{
		if (xinter <= 0 || xinter >= game->width || yinter <= 0 || yinter >= game->height)
			break;
		// printf("%f : %f\n", yinter, xinter);

		if (game->map[(int)(yinter / TILE)][(int)(xinter / TILE)] == '1'){
			// printf("%f : %f || \n", yinter, xinter);
			// draw_point(game, xinter, yinter);
			double dis = sqrt(pow(xinter - game->ply.x, 2) + pow(yinter - game->ply.y, 2));
			if (ray->distance_to_wall > dis)
			{
				ray->distance_to_wall = dis;
				ray->wall_hitx = xinter;
				ray->wall_hity = yinter;
				ray->horizantal_intersection = 0;

			}
			// if (xinter >= 10 && xinter < game->width - 10 && yinter >= 10 && yinter < game->height - 10) 
			// 	draw_point(game, xinter, yinter);

			return ;
		}
		xinter += xstep;
		yinter += ystep;
	}
}



void	project_wall(t_game *game, int x, t_ray *ray)
{
	double	wall_height;
	int		wall_start_y;
	int		wall_end_y;
	int		y;

	wall_height = TILE * ((double)(WIDTH / 2.0) / tan(FOV / 2.0))
		/ ray->distance_to_wall;
	wall_start_y = (double)HEIGHT / 2.0 - (wall_height / 2.0);
	if (wall_start_y < 0)
		wall_start_y = 0;
	wall_end_y = ((double)HEIGHT / 2.0) + (wall_height / 2.0);
	if (wall_end_y >= HEIGHT)
		wall_end_y = HEIGHT - 1;
	y = 0;
	while (y < wall_start_y)
		mlx_put_pixel(game->img, x, y++, game->ceil_color);
	while (y <= wall_end_y)
	{
		mlx_put_pixel(game->img, x, y, get_texture_color(
				get_correct_texture(game, ray), ray, wall_height, y));
		y++;
	}
	while (y < HEIGHT)
		mlx_put_pixel(game->img, x, y++, game->floor_color);
}

void	cast_rays(t_game *game)
{
	t_ray	ray;
	int		x;

	ray.angle = game->ply.angle - FOV / 2.0;
	x = 0;
	while (x < WIDTH)
	{
		horizantal_intersection(game, &ray),
		vertical_intersection(game, &ray);
		ray.distance_to_wall *= cos(ray.angle - game->ply.angle);
		project_wall(game, x, &ray);
		ray.angle += FOV / (double)WIDTH;
		x++;
	}
}
