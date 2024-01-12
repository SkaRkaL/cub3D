/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakarkal <sakarkal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:03:30 by sakarkal          #+#    #+#             */
/*   Updated: 2024/01/12 02:37:42 by sakarkal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include "gnl/gnl.h"

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
	char	**map;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	t_color	c;
	t_color	f;
}					t_map;

////////////////////////    UTILS     ///////////////////////////

void	exit_err(char *str);

void	check_args(int ac, char **av);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, int len);
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
void	check_duplicates(short flag, short full_flag);
void	check_textures_colors(char *trimmed_line, short *flag, t_map *map);
void	read_textures(int fd, t_map *map);
void	fill_map(t_map *map);
void	read_map(int fd, t_map *map);
void	check_map_errors(t_map *map);
int		empty_line(char *line, t_map *map, bool *is_map);

#endif
