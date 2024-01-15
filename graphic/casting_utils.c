/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asettar <asettar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:43:20 by asettar           #+#    #+#             */
/*   Updated: 2024/01/15 18:43:21 by asettar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

bool	check_horz_intr(double xinter, double yinter, t_ray *ray, t_game *game)
{
	if (game->map[(int)(yinter / TILE)][(int)(xinter / TILE)] == '1'
		|| (sin(ray->angle) < 0 &&
		game->map[(int)((yinter - 1) / TILE)][(int)(xinter / TILE)] == '1'))
	{
		ray->wall_hitx = xinter;
		ray->wall_hity = yinter;
		ray->horizantal_intersection = 1;
		ray->distance_to_wall = sqrt(pow(xinter - game->ply.x, 2)
				+ pow(yinter - game->ply.y, 2));
		return (1);
	}
	return (0);
}

bool	check_vert_intr(double xinter, double yinter, t_ray *ray, t_game *game)
{
	double	dis;

	if (game->map[(int)(yinter / TILE)][(int)(xinter / TILE)] == '1'
		|| (cos(ray->angle) < 0 &&
		game->map[(int)(yinter / TILE)][(int)((xinter - 1) / TILE)] == '1'))
	{
		dis = sqrt(pow(xinter - game->ply.x, 2) + pow(yinter - game->ply.y, 2));
		if (ray->distance_to_wall > dis)
		{
			ray->distance_to_wall = dis;
			ray->wall_hitx = xinter;
			ray->wall_hity = yinter;
			ray->horizantal_intersection = 0;
		}
		return (1);
	}
	return (0);
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
