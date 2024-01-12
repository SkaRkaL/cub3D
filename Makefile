NAME = cub3D

SRC	=	main.c \
		gnl/gnl_utils.c \
		gnl/gnl.c \
		lib/ft_atoi.c \
		lib/ft_printer.c \
		lib/ft_strcmp.c \
		lib/ft_memset.c \
		lib/ft_repeat.c \
		lib/ft_split.c \
		lib/ft_strtok.c \
		lib/ft_strtrim.c \
		lib/ft_strchr.c \
		utils/check_duplicated.c \
		utils/check_empty_line.c \
		utils/check_in_border.c \
		utils/check_map_errs.c \
		utils/check_textures_color.c \
		utils/exit_err.c \
		utils/fill_map.c \
		utils/insert_colors.c \
		utils/is_a_mem_player.c \
		utils/read_map.c \
		utils/read_textures.c \
		utils/set_colors.c 


OBJ = $(SRC:.c=.o)

CC  = cc

# CFLAGS = -Wall -Wextra -Werror #-L libft -lft -lmlx -framework OpenGL -framework AppKit
# CFLAGS =  -fsanitize=address -g

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

.o: .c cub3D.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
