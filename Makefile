CC		 =  cc
CFLAGS	 =  -Wall -Werror -Wextra
NAME	 =  cub3D
MLX      =  MLX/libmlx42.a
MLXFLAGS =  -framework Cocoa -framework OpenGL -framework IOKit -lglfw
INCLUDE  =  -I/Users/${USER}/homebrew/Cellar/glfw/3.3.9/include/GLFW
LIB      =  -L/Users/${USER}/homebrew/Cellar/glfw/3.3.9/lib


SRCS	= main.c \
		graphic/player_mouvements.c \
		graphic/casting.c \
		graphic/graphic_handle.c \
		graphic/textures.c \
		graphic/casting_utils.c \
		gnl/gnl_utils.c \
		gnl/gnl.c \
		libft/ft_atoi.c \
		libft/ft_printer.c \
		libft/ft_strcmp.c \
		libft/ft_memset.c \
		libft/ft_repeat.c \
		libft/ft_split.c \
		libft/ft_strtok.c \
		libft/ft_strtrim.c \
		libft/ft_strchr.c \
		parsing/read_map.c \
		parsing/read_map_utils.c \
		parsing/read_textures.c \
		parsing/read_textures_utils.c
OBJS	= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(MLXFLAGS) $(OBJS)  $(MLX) $(LIB) -o $(NAME)

%.o: %.c cub3D.h gnl/gnl.h
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
re : fclean all
.PHONY : all clean fclean re
