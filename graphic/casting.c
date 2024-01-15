/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asettar <asettar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:43:04 by asettar           #+#    #+#             */
/*   Updated: 2024/01/15 18:43:05 by asettar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	horizantal_intersection(t_game *game, t_ray *ray)
{
	double	xinter;
	double	yinter;
	double	ystep;
	double	xstep;

	yinter = floor(game->ply.y / TILE) * TILE;
	if (sin(ray->angle) > 0)
		yinter += TILE;
	xinter = (yinter - game->ply.y) / tan(ray->angle) + game->ply.x;
	ystep = TILE;
	if (sin(ray->angle) < 0)
		ystep *= -1;
	xstep = ystep / tan(ray->angle);
	while (1)
	{
		if (xinter <= 0 || xinter >= game->width
			|| yinter <= 0 || yinter >= game->height)
			break ;
		if (check_horz_intr(xinter, yinter, ray, game))
			return ;
		xinter += xstep;
		yinter += ystep;
	}
	ray->distance_to_wall = INT_MAX;
}

void	vertical_intersection(t_game *game, t_ray *ray)
{
	double	xinter;
	double	yinter;
	double	xstep;
	double	ystep;

	xinter = floor(game->ply.x / TILE) * TILE;
	if (cos(ray->angle) > 0)
		xinter += TILE;
	yinter = (xinter - game->ply.x) * tan(ray->angle) + game->ply.y;
	xstep = TILE;
	if (cos(ray->angle) < 0)
		xstep *= -1;
	ystep = xstep * tan(ray->angle);
	while (1)
	{
		if (xinter <= 0 || xinter >= game->width
			|| yinter <= 0 || yinter >= game->height)
			break ;
		if (check_vert_intr(xinter, yinter, ray, game))
			return ;
		xinter += xstep;
		yinter += ystep;
	}
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
