/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakarkal <sakarkal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:03:30 by sakarkal          #+#    #+#             */
/*   Updated: 2024/01/11 17:06:37 by sakarkal         ###   ########.fr       */
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

int		check_line_is_empty(char *line);

////////////////////////    UTILS     ///////////////////////////

char	*ft_strdup(char *s1);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, int len);
char	**ft_split(char *str, char c);
int		ft_atoi(const char *str);
char	*ft_strtrim(char const *s, char const *set);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, int len);
int		ft_strlcpy(char *dst, const char *src, int dstsize);
char	*ft_strtok(char *str, char *sep);

#endif
