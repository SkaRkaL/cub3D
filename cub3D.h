#ifndef CUB3D_H
# define CUB3D_H

#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include "gnl/gnl.h"


typedef struct s_map
{
	int		x;
	int		y;
	char	**map;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		f;
	int		c;
}				t_map;



////////////////////////    UTILS     ///////////////////////////
char	*ft_strdup(char *s1);
int		ft_strchr(char *s, int c);
char	*ft_substr(char *s, unsigned int start, int len);
char	**ft_split(char *str, char c);




#endif
