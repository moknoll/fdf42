# Compiler & Flags
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -Iincludes -Ilibft -IMLX42/include
LDFLAGS = -Llibft -LMLX42/build -lft -lmlx42 \
          -lGL -lGLU -lX11 -lm -lXext -lpthread -lglfw

# Source Files
SRC = src/main.c \
      src/parse_map.c \
      src/parse_line.c \
      src/utils.c \
      src/render.c \
      src/drawing.c \
      src/color.c \
      src/projection.c \
      src/drawing_utils.c \
      src/hooks.c \
      src/parse_map_utils.c \
      src/utils_two.c

OBJ = $(SRC:.c=.o)
NAME = fdf
LIBFT = libft/libft.a

# Default Target
all: $(NAME)

# Build main project
$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

# Build libft
$(LIBFT):
	@$(MAKE) -C libft

# Compile object files
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

# Clean object files and libft
clean:
	@rm -f $(OBJ)
	@$(MAKE) -C libft clean

# Clean all
fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C libft fclean

# Rebuild project
re: fclean all

.PHONY: all clean fclean re
