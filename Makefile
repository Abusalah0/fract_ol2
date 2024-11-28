CC = cc
CFLAGS = -Wall -Werror -Wextra
MLX_FLAGS = -I./minilibx-linux -L./minilibx-linux -lmlx -lXext -lX11 -lm

SRC = main.c fractals.c key_events.c
OBJ = $(SRC:.c=.o)
NAME = mandelbrot

DONUT_C = donut.c
DONUT_O = $(DONUT_C:.c=.o)
DONUT = donut

# Paths for libft
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(MLX_FLAGS) $(LIBFT_FLAGS)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c fract_ol.h
	$(CC) $(CFLAGS) -c $< -o $@

donut: $(DONUT_O)
	$(CC) $(CFLAGS) -lm -o $(DONUT) $(DONUT_O)
	./$(DONUT)

clean: clean_donut clean_libft
	rm -rf $(OBJ)

fclean: clean fclean_donut fclean_libft
	rm -rf $(NAME)

clean_donut:
	rm -rf $(DONUT_O)

fclean_donut: clean_donut
	rm -rf $(DONUT)

clean_libft:
	$(MAKE) -C $(LIBFT_DIR) clean

fclean_libft:
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all re clean fclean clean_libft fclean_libft clean_donut fclean_donut donut run_donut