/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asettar <asettar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:03:30 by sakarkal          #+#    #+#             */
/*   Updated: 2024/01/14 23:59:56 by asettar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include "gnl/gnl.h"
#include <limits.h>
#include <math.h>
#include "MLX/MLX42.h"


#define WIDTH 1200
#define HEIGHT 900
#define SPEED 4
#define FOV M_PI / 3.0
#define TILE 64.0

typedef struct s_player
{
	double x;
	double y;
	double wall_hitx;
	double wall_hity;
	double angle;
} t_player;

typedef struct s_ray 
{
	double wall_hitx;
	double wall_hity;
	double horizantal_intersection;
	double distance_to_wall;
	double angle;
} t_ray;

typedef struct s_game
{
	char **map;
	int height;
	int width;
	uint32_t ceil_color;
	uint32_t floor_color;
	t_player	ply;
	mlx_image_t* img;
	mlx_t *mlx;
	mlx_texture_t *no_texture;
	mlx_texture_t *ea_texture;
	mlx_texture_t *so_texture;
	mlx_texture_t *we_texture;
}	t_game;

typedef struct s_var
{
	int		i;
	char	*dir;
	char	*path;
}			t_var;

typedef union u_color
{
	uint32_t		value;
	struct
	{
		uint8_t		a;
		uint8_t		b;
		uint8_t		g;
		uint8_t		r;
	};
}			t_color;

typedef struct s_map
{
	int		height;
	int		width;
	int		x;
	int		y;
	char	orientation;
	char	**map;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	t_color	c;
	t_color	f;
}					t_map;

////////////////////////    UTILS     ///////////////////////////

void	exit_err(char *str, t_map *map);

void	check_args(int ac, char **av);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, unsigned int len);
char	**ft_split(char *str, char c);
int		ft_atoi(const char *str);
char	*ft_strtrim(char const *s, char const *set);
char	*ft_strchr(const char *s, int c);
int		ft_strlcpy(char *dst, const char *src, int dstsize);
int		ft_strncmp(char *s1, char *s2, int n);
void	*ft_memset(void *b, int c, size_t n);
char	*ft_strtok(char *str, char *sep);
void	*check_isfree(char **str);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
char	*ft_repeat(char c, size_t a);

int		set_color(char **color);
void	insert_colors(char *path, t_map *map, int i);
int		check_commas(char *str);
int		invalid_number(char *str);
bool	is_a_player(char c);
bool	is_a_member(char c);
void	check_in_border(int i, int j, t_map *map);
void	check_duplicates(short flag, short full_flag, t_map *map);
void	check_textures_colors(char *trimmed_line, short *flag, t_map *map);
void	read_textures(int fd, t_map *map);
void	fill_map(t_map *map);
void	read_map(int fd, t_map *map);
void	check_map_errors(t_map *map);
int		empty_line(char *line, t_map *map, bool *is_map);

void	clear_exit(t_game *game, int exit_status);
void	graphic_handle(t_map *map);
void	draw_point(t_game *game, double x, double y);
void	draw_line(t_game *game);
void	draw_rectangle(t_game *game, int y, int x, int color);
void	draw_map(t_game *game);
void	hook_handle(void *data);
void	cast_rays(t_game *game);
uint32_t	get_texture_color(mlx_texture_t *text, t_ray *ray, double wh, int y);
mlx_texture_t	*get_correct_texture(t_game *game, t_ray *ray);
#endif
