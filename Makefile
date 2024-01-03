NAME = cub3D

SRC = main.c gnl/gnl_utils.c gnl/gnl.c split.c

OBJ = $(SRC:.c=.o)

CC  = cc

# CFLAGS = -Wall -Wextra -Werror #-L libft -lft -lmlx -framework OpenGL -framework AppKit
# CFLAGS =  -g -Wall 

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

.o: .c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
