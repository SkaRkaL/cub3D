/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_mouvements.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asettar <asettar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:43:17 by asettar           #+#    #+#             */
/*   Updated: 2024/01/15 18:44:09 by asettar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	chek_wall_collision(t_game *game, double newy, double newx)
{
	if (game->map[(int)(newy / TILE)][(int)(newx / TILE)] != '1' &&
		game->map[(int)((newy + 5.0) / TILE)][(int)((newx) / TILE)] != '1' &&
		game->map[(int)((newy - 5.0) / TILE)][(int)((newx) / TILE)] != '1' &&
		game->map[(int)((newy) / TILE)][(int)((newx - 5.0) / TILE)] != '1' &&
		game->map[(int)((newy) / TILE)][(int)((newx + 5.0) / TILE)] != '1')
	{
		game->ply.x = newx;
		game->ply.y = newy;
	}
}

void	my_close_callback(void *param)
{
	clear_exit(param, EXIT_SUCCESS);
}

void	check_player_mouvements(t_game *game, double newx, double newy)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		newx += cos(game->ply.angle) * SPEED;
		newy += sin(game->ply.angle) * SPEED;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		newx -= cos(game->ply.angle) * SPEED;
		newy -= sin(game->ply.angle) * SPEED;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		newx += sin(game->ply.angle) * SPEED;
		newy -= cos(game->ply.angle) * SPEED;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		newx -= sin(game->ply.angle) * SPEED;
		newy += cos(game->ply.angle) * SPEED;
	}
	chek_wall_collision(game, newy, newx);
}

void	hook_handle(void *data)
{
	t_game	*game;
	double	newx;
	double	newy;

	game = data;
	newx = game->ply.x;
	newy = game->ply.y;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		clear_exit(game, EXIT_SUCCESS);
	mlx_close_hook(game->mlx, my_close_callback, game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		game->ply.angle -= 0.05;
	else if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		game->ply.angle += 0.05;
	check_player_mouvements(game, newx, newy);
	cast_rays(game);
}
