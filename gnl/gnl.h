#ifndef GNL_H
# define GNL_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 11
# endif

int		ft_strlen(char *s);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_search(char *str, int c);
char	*get_next_line(int fd);

#endif