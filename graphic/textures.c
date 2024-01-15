/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asettar <asettar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:43:24 by asettar           #+#    #+#             */
/*   Updated: 2024/01/15 18:43:25 by asettar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

uint32_t	get_texture_color(mlx_texture_t *text, t_ray *ray, double wh, int y)
{
	int				text_offset_x;
	int				text_offset_y;
	unsigned int	index;
	int				wall_start;
	uint8_t			*pixels;

	wall_start = ((double)HEIGHT / 2.0) - (wh / 2.0);
	if (ray->horizantal_intersection)
		text_offset_x = fmod(ray->wall_hitx, TILE) * (double)text->width / TILE;
	else
		text_offset_x = fmod(ray->wall_hity, TILE) * (double)text->width / TILE;
	text_offset_y = (y - wall_start) * (double)text->height / wh;
	index = text_offset_y * text->width * text->bytes_per_pixel
		+ text_offset_x * text->bytes_per_pixel;
	pixels = text->pixels;
	if (index < 0
		|| index >= text->width * text->height * text->bytes_per_pixel)
		return (0);
	return (pixels[index] << 24 | pixels[index + 1] << 16
		| pixels[index + 2] << 8 | pixels[index + 3]);
}

mlx_texture_t	*get_correct_texture(t_game *game, t_ray *ray)
{
	if (ray->horizantal_intersection)
	{
		if (sin(ray->angle) < 0)
			return (game->no_texture);
		return (game->so_texture);
	}
	else
	{
		if (cos(ray->angle) < 0)
			return (game->ea_texture);
		return (game->we_texture);
	}
}
